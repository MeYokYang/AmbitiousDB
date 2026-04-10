#ifndef COLLECTION_H
#define COLLECTION_H

#include "standard.h"
#include "object.h"
#include "code.h"


template <typename T>
class Collection : public Object
{
private:

public:
    virtual ulong getMaxLen() const = 0;
    virtual ulong len() const = 0;

    virtual code reverse() = 0;
    virtual code clear() = 0;

    virtual ~Collection() = default;
};



#endif // COLLECTION_H
