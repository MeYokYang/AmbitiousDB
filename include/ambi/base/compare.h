#ifndef AT_COMPARE_H
#define AT_COMPARE_H

#include "ambi/base/type.h"

namespace atdb {


enum class CmpResult {
    CMP_UNKNOWN = 2,
    CMP_GREATER = 1,
    CMP_EQUAL   = 0,
    CMP_LESS    = -1
};
    
static const atbool ret_and[3][3] = {
    {FALSE, FALSE, FALSE},
    {FALSE, TRUE, UNKNOWN},
    {FALSE, UNKNOWN, UNKNOWN}
};

static const atbool ret_or[3][3] = {
    {FALSE, TRUE, UNKNOWN},
    {TRUE, TRUE, TRUE},
    {UNKNOWN, TRUE, UNKNOWN}
};

    
} // end namespace atdb

#endif // AT_COMPARE_H
