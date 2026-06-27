#ifndef AMBI_QUEUE_H
#define AMBI_QUEUE_H

#include "standard.h"
#include "container.h"

namespace ambi {

template <typename T>
class Queue : public Collection<T> {
protected:
    _coll_size_t        size;
    _coll_size_t        front;
    _coll_size_t        back;

public:
    virtual ~Queue() = default;

    virtual boolean full() const { return len == size ? TRUE : FALSE; }
    virtual _coll_size_t size() const { return size; }
    virtual _coll_size_t length() const { return len; }
    virtual boolean enqueue(const T& d) = 0;
    virtual boolean dequeue() = 0;
    virtual boolean peek() = 0;

};



} // namespace ambi

#endif // AMBI_QUEUE_H
