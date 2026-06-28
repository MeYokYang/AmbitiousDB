#ifndef AT_FORMAT_H
#define AT_FORMAT_H

#include "ambi/base/type.h"

#define INLINE  inline

#define THROW_IF_NULL(p, c)         if (NULL == (p)) throw c;
#define THROW_IF_NOT_TRUE(b, c)     if (TRUE == (b)) throw c;

namespace atdb {

atvoid at_assert(atbool b);


} // end namespace atdb

#endif // AT_FORMAT_H
