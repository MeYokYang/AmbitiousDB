#ifndef AMBI_OBJECT_H
#define AMBI_OBJECT_H

#include "standard.h"
#include "str.h"

namespace ambi {

#define     _obj_hash_code_type     ulong

class Object
{
public:
    virtual ~Object() = default;

    virtual _obj_hash_code_type hashCode() const = 0;
    virtual boolean equals(const Object& o) const { return this == &o ? TRUE : FALSE; }
    virtual Object clone() const = 0;
    virtual Str toString() const = 0;
    // notify() notifyAll() wait() finalize()

};

} // namespace ambi

#endif // AMBI_OBJECT_H
