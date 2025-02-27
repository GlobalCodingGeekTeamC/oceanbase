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

#ifndef _OBMYSQL_ERRNO_H_
#define _OBMYSQL_ERRNO_H_

#include <mariadb/mysqld_error.h>

#define ER_AES_INVALID_IV 1882
#define ER_OVERSIZE_NEED_RETRY 1887
#define ER_AGGREGATE_ORDER_FOR_UNION 3028
#define ER_INCORRECT_TYPE 3064
#define ER_ACCOUNT_HAS_BEEN_LOCKED 3118
#define ER_NON_DEFAULT_VALUE_FOR_GENERATED_COLUMN 3105
#define ER_DEPENDENT_BY_GENERATED_COLUMN 3108

#define ER_INVALID_JSON_TEXT 3140
#define ER_INVALID_JSON_TEXT_IN_PARAM 3141
#define ER_INVALID_JSON_BINARY_DATA 3142
#define ER_INVALID_JSON_PATH 3143
#define ER_INVALID_JSON_CHARSET 3144
#define ER_INVALID_JSON_CHARSET_IN_FUNCTION 3145
#define ER_INVALID_TYPE_FOR_JSON 3146
#define ER_INVALID_CAST_TO_JSON 3147
#define ER_INVALID_JSON_PATH_CHARSET 3148
#define ER_INVALID_JSON_PATH_WILDCARD 3149
#define ER_JSON_VALUE_TOO_BIG 3150
#define ER_JSON_KEY_TOO_BIG 3151
#define ER_JSON_USED_AS_KEY 3152
#define ER_JSON_VACUOUS_PATH 3153
#define ER_JSON_BAD_ONE_OR_ALL_ARG 3154
#define ER_NUMERIC_JSON_VALUE_OUT_OF_RANGE 3155
#define ER_INVALID_JSON_VALUE_FOR_CAST 3156
#define ER_JSON_DOCUMENT_TOO_DEEP 3157
#define ER_JSON_DOCUMENT_NULL_KEY 3158
#define ER_INVALID_JSON_PATH_ARRAY_CELL 3165

#define ER_TOO_BIG_ENUM 3504
#define ER_TOO_LONG_SET_ENUM_VALUE 3505
#define ER_TOO_MANY_TENANT_PARTITIONS_ERROR 3506

#define ER_MISSING_JSON_VALUE 3966
#define ER_MULTIPLE_JSON_VALUES 3967

#endif
