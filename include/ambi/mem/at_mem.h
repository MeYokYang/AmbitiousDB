#ifndef AT_MEM_H
#define AT_MEM_H

#include "ambi/base/at_type.h"

namespace atdb {


atvoid at_memcpy(atbyte* dst, atulong dst_len, atbyte* src, atulong src_len);

atvoid at_memset(atbyte* dst, atulong dst_len, atbyte c);


} // end namespace atdb

#endif // AT_MEM_H
