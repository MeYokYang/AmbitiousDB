#ifndef AMBI_COLLECTION_H
#define AMBI_COLLECTION_H

#include "ambi/standard.h"
#include "ambi/lang/iterable.h"
#include "ambi/lang/arr.h"

namespace ambi {

#define     _coll_size_t        sint
//#define     _coll_max_len       get_type_max(_coll_size_t)
//#define     _coll_size_none     get_type_none(_coll_size_t)

template <typename T>
class Collection : public Object, public Iterable<T>
{
public:
    virtual ~Collection() = default;

    virtual _coll_size_t size() const = 0;
    virtual boolean isEmpty() const = 0;
    virtual boolean contains(const T& d) const = 0;
    virtual Arr<T> toArray() const = 0;
    virtual boolean add(const T& d) = 0;
    virtual boolean remove(const T& d) = 0;
    virtual boolean containsAll(const Collection<T>& c) const = 0;
    virtual boolean addAll(const Collection<T>& c) = 0;
    virtual boolean removeAll(const Collection<T>& c) = 0;
    //virtual boolean removeIf(Predicate<T> pred) = 0;
    virtual bollean retainAll(const Collection<T>& c) = 0;
    virtual clear() = 0;
    virtual boolean equals(const Collection<T>& c) const = 0;

};

} // namespace ambi 

#endif // AMBI_COLLECTION_H
