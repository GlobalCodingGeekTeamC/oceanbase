/**
 * Copyright (c) 2021 OceanBase
 * OceanBase CE is licensed under Mulan PubL v2.
 * You can use this software according to the terms and conditions of the Mulan PubL v2.
 * You may obtain a copy of Mulan PubL v2 at:
 *          http://license.coscl.org.cn/MulanPubL-2.0
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
 * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PubL v2 for more details.
 */

#ifndef OCEANBASE_BASIC_OB_SET_OB_MERGE_SET_OP_H_
#define OCEANBASE_BASIC_OB_SET_OB_MERGE_SET_OP_H_

#include "sql/engine/set/ob_set_op.h"
#include "share/datum/ob_datum_funcs.h"
#include "sql/engine/basic/ob_chunk_datum_store.h"

namespace oceanbase {
namespace sql {

class ObMergeSetSpec : public ObSetSpec {
  OB_UNIS_VERSION_V(1);

public:
  ObMergeSetSpec(common::ObIAllocator& alloc, const ObPhyOperatorType type);
};

class ObMergeSetOp : public ObOperator {
public:
  ObMergeSetOp(ObExecContext& exec_ctx, const ObOpSpec& spec, ObOpInput* input);

  virtual int inner_open() override;
  virtual int inner_close() override;
  virtual int rescan() override;
  virtual void destroy() override;
  class Compare {
  public:
    Compare() : sort_collations_(nullptr), cmp_funcs_(nullptr), ret_code_(common::OB_SUCCESS)
    {}
    int init(const common::ObIArray<ObSortFieldCollation>* sort_collations,
        const common::ObIArray<common::ObCmpFunc>* cmp_funcs);
    int operator()(
        const common::ObIArray<ObExpr*>& l, const common::ObIArray<ObExpr*>& r, ObEvalCtx& eval_ctx, int& cmp);
    int operator()(
        const ObChunkDatumStore::StoredRow& l, const common::ObIArray<ObExpr*>& r, ObEvalCtx& eval_ctx, int& cmp);
    const common::ObIArray<ObSortFieldCollation>* sort_collations_;
    const common::ObIArray<common::ObCmpFunc>* cmp_funcs_;
    int ret_code_;
  };

protected:
  int do_strict_distinct(ObOperator& child_op, const common::ObIArray<ObExpr*>& compare_row,
      const common::ObIArray<ObExpr*>*& row, int& cmp);
  template <typename T>
  int do_strict_distinct(ObOperator& child_op, const T* compare_row, const common::ObIArray<ObExpr*>*& output_row);

  int convert_row(const ObChunkDatumStore::StoredRow* sr, const common::ObIArray<ObExpr*>& exprs);
  int convert_row(const common::ObIArray<ObExpr*>& src_exprs, const common::ObIArray<ObExpr*>& dst_exprs);

  bool get_need_skip_init_row() const
  {
    return need_skip_init_row_;
  }
  void set_need_skip_init_row(bool need_skip_init_row)
  {
    need_skip_init_row_ = need_skip_init_row;
  }

protected:
  common::ObArenaAllocator alloc_;
  ObChunkDatumStore::LastStoredRow<> last_row_;
  Compare cmp_;
  bool need_skip_init_row_;
  bool iter_end_;
};

template <typename T>
int ObMergeSetOp::do_strict_distinct(
    ObOperator& child_op, const T* compare_row, const common::ObIArray<ObExpr*>*& output_row)
{
  int ret = OB_SUCCESS;
  int cmp_ret = 0;
  bool is_break = false;
  while (OB_SUCC(ret) && !is_break) {
    if (OB_FAIL(child_op.get_next_row())) {
      if (OB_ITER_END != ret) {
        SQL_ENG_LOG(WARN, "failed to get next row", K(ret));
      }
    } else if (OB_UNLIKELY(get_need_skip_init_row())) {
      set_need_skip_init_row(false);
      is_break = true;
      if (OB_NOT_NULL(compare_row)) {
        ret = OB_ERR_UNEXPECTED;
        SQL_ENG_LOG(WARN, "first row: compare row must be null", K(ret));
      } else if (OB_FAIL(last_row_.save_store_row(child_op.get_spec().output_, eval_ctx_, 0))) {
        SQL_ENG_LOG(WARN, "failed to save right row", K(ret));
      }
    } else if (OB_NOT_NULL(compare_row)) {
      if (OB_FAIL(cmp_(*compare_row, child_op.get_spec().output_, eval_ctx_, cmp_ret))) {
        SQL_ENG_LOG(WARN, "strict compare with last_row failed", K(ret), K(compare_row));
      } else if (0 != cmp_ret) {
        is_break = true;
      }
    } else {
      ret = OB_ERR_UNEXPECTED;
      SQL_ENG_LOG(WARN, "unexpected status", K(ret));
    }
  }
  if (OB_SUCC(ret)) {
    output_row = &child_op.get_spec().output_;
  }
  return ret;
}

}  // end namespace sql
}  // end namespace oceanbase

#endif  // OCEANBASE_BASIC_OB_SET_OB_MERGE_SET_OP_H_
