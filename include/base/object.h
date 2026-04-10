#ifndef OBJECT_H
#define OBJECT_H

#include "standard.h"


class Object
{
private:

public:
    Object();
    virtual ~Object();

    const ulong hashCode() const ;
    const char* toString() const ;
    bool equals(const Object& other) const ;
};

#endif // OBJECT_H
