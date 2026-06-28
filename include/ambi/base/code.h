#ifndef AT_CODE_H
#define AT_CODE_H

#include "ambi/base/type.h"

namespace atdb {


enum class Code : uint
{
    AT_SUCCESS          = 0,

    // operate
    NULL_POINTER        = 1000,
    OUT_OF_RANGE        = 1001,
    
    // mem
    OUT_OF_MEMORY       = 2000,
    MEMPOOL_INIT_ERR    = 2001,

};


} // namespace atdb

#endif // atdb_CODE_H
