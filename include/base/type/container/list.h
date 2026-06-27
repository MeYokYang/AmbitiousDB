#ifndef AMBI_LIST_H
#define AMBI_LIST_H

#include "standard.h"
#include "container.h"

namespace ambi {


template <typename T>
class List : public Collection<T>
{
public:
    virtual ~List() = default;

    virtual boolean insert(const T& d, _coll_size_t pos = _coll_size_none) = 0;
    virtual boolean insertFirst(const T& d) { return insert(d, 0); }
    virtual boolean insertLast(const T& d) { return insert(d); }
    virtual boolean remove(_coll_size_t pos = _coll_size_none) = 0;
    virtual boolean removeFirst() { return remove(0); }
    virtual boolean removeLast() { return remove(); }

};

template <typename T>
class LinkedList : public List<T>
{
private:
    class Node
    {
    public:
        T       data;
        Node*   prev;
        Node*   next;

        Node(const T& d, Node* p = NULL, Node* n = NULL) : data(d), prev(p), next(n) {}

    };

    Node*       head;
    Node*       tail;

public:
    LinkedList() : head(NULL), tail(NULL) {}
    


};


} // namespace ambi

#endif // AMBI_LIST_H
