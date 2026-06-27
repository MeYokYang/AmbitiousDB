#ifndef AMBI_ITERATOR_H
#define AMBI_ITERATOR_H

#include "standard.h"

namespace ambi {

template <typename T>
class Iterator
{
public:
    virtual boolean hasNext() const = 0;
    virtual T next() = 0;
    //void remove() {}
    //virtual void forEach(Consumer<T> consumer) = 0;

};

} // namespace ambi

#endif // AMBI_ITERATOR_H
