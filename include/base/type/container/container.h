#ifndef AMBI_CONTAINER_H
#define AMBI_CONTAINER_H

#include "standard.h"
#include "tag.h"
#include "arr.h"

namespace ambi {

#define     _coll_size_t        ulong
#define     _coll_max_len       get_type_max(_coll_size_t)
#define     _coll_size_none     get_type_none(_coll_size_t)

template <typename T>
class Collection : public Iterable<T>
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
    

protected:
    static const _coll_size_t   MAX_LEN = _coll_max_len;
    _coll_size_t                len;

public:
    Collection(_coll_size_t l) : len(l) {}
    virtual ~Collection() = default;

    virtual _coll_size_t size() const = 0;
    virtual boolean empty() const = 0;
    virtual boolean contains(const T& d) const = 0;
    virtual boolean add(const T& d) = 0;
    virtual boolean remove(const T& d) = 0;
    virtual void clear() = 0;

    virtual boolean addAll(const Collection<T>& c) = 0;
    virtual boolean removeAll(const Collection<T>& c) = 0;
    virtual boolean retainAll(const Collection<T>& c) = 0;
    virtual boolean containsAll(const Collection<T>& c) const = 0;

    virtual Arr<T> toArray() const = 0;

    // itor

};

template <typename T>
class Map
{
private:

public:

};


} // namespace ambi 

#endif // AMBI_CONTAINER_H
