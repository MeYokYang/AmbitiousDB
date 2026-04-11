#ifndef COLLECTION_H
#define COLLECTION_H

#include "object.h"
#include "tag.h"
#include "standard.h"


template <typename T>
class Collection : public Object
    //, public Iterable<T>
{
public:
    virtual bool isEmpty() const = 0;
    virtual bool clear() = 0;

};

template <typename T>
class List : public Collection<T>
{
protected:
    static const ulong  MAX_LEN = ULONG_MAX;
    ulong               len;

public:
    bool isEmpty() const override { return len == 0 ? TRUE : FALSE; }
    ulong length() const { return len; }
    virtual bool insert(const T& d, ulong pos = ULONG_NONE) = 0;
    virtual bool insertFirst(const T& d) { return insert(d, 0); }
    virtual bool insertLast(const T& d) { return insert(d); }
    virtual bool remove(ulong pos = ULONG_NONE) = 0;
    virtual bool removeFirst() { return remove(0); }
    virtual bool removeLast() { return remove(); }

};

template <typename T>
class Queue : public Collection<T>
{
protected:
    static const ulong  MAX_LEN = ULONG_MAX;
    ulong               len;

public:

};

template <typename T>
class Set : public Collection<T>
{
protected:
    static const ulong  MAX_LEN = ULONG_MAX;
    ulong               len;

public:

};

template <typename T>
class Map : public Object
{
private:

public:

};

#endif // COLLECTION_H
