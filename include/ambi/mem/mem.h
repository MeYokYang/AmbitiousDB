#ifndef AT_MEM_H
#define AT_MEM_H

#include "ambi/base/type.h"

namespace atdb {


atvoid at_memcpy(atbyte* dst, ulong dst_len, atbyte* src, ulong src_len);

atvoid at_memset(atbyte* dst, ulong dst_len, atbyte c);


} // end namespace atdb

#endif // AT_MEM_H
