#include "ambi/mem/mem.h"
#include "ambi/base/format.h"
#include "ambi/base/code.h"
#include <cstring>

namespace atdb {

atvoid at_memcpy(atbyte* dst, ulong dst_len, atbyte* src, ulong src_len) {
    at_assert(NULL != dst && NULL != src);
    at_assert(dst != src && dst_len >= src_len);
    at_assert(!(src >= dst && src <= dst + dst_len));
    at_assert(!(dst >= src && dst <= src + src_len));

    if (!(NULL != dst && NULL != src))
        throw Code::NULL_POINTER;

    if (!(dst != src && dst_len >= src_len) ||
        (src >= dst && src <= dst + dst_len) ||
        (dst >= src && dst <= src + src_len)
    )
        throw Code::OUT_OF_RANGE;

    std::memcpy(dst, src, src_len);
}

atvoid at_memset(atbyte* dst, ulong dst_len, atbyte c) {
    at_assert(NULL != dst && dst_len > 0);

    if (!(NULL != dst && dst_len > 0))
        throw Code::NULL_POINTER;

    std::memset(dst, c, dst_len);
}


} // end namespace atdb
