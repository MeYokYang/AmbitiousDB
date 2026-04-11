#ifndef OBJECT_H
#define OBJECT_H

#include "standard.h"


class Object
{
private:

public:
    virtual ~Object() = default;

    const ulong hashCode() const ;
    const char* toString() const ;
    bool equals(const Object& other) const ;
};

#endif // OBJECT_H
