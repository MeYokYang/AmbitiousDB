#ifndef LIST_H
#define LIST_H

#include "standard.h"
#include "collection.h"


/**
 * @brief List collection
 */
template <typename T>
class List : public Collection<T>
{
private:
    static const ulong MAX_LEN;
    ulong len;

public:
    ulong getMaxLen() const override { return MAX_LEN; };
    ulong len() const override { return len; };
};


template <typename T>
class LinkedList : public List<T>
{
private:
    class node<T>
    {
    private:
        T       data;
        node*   next;
        node*   prev;
    public:

    };

    node<T>* head;
    node<T>* tail;
public:
    LinkedList() : head(NULL), tail(NULL) {};
    ~LinkedList();

    code insertFirst(const T& data);
    code insertLast(const T& data);
    code insertAt(const T& data, ulong pos);

    code deleteFirst();
    code deleteLast();
    code deleteAt(ulong pos);
};




template <typename T>
class ArrayList : public List<T>
{
private:
    T* data;

public:

};




#endif // LIST_H
