#ifndef QUEUE_H
#define QUEUE_H

#include "collection.h"
#include "arr.h"

template <typename T>
class PriorityQueue : public Queue
{
private:

public:

};


template <typename T>
class ArrayDeque : public Queue
{
private:
    Arr<T>      arr;

public:
    ArrayDeque(ulong s = ULONG_NONE) : arr() { this->size = arr.length(); this->len = 0; this->front = 0; this->back = 0; }
    ~ArrayDeque() = default;
    ArrayDeque(const ArrayDeque& other) = default;
    ArrayDeque& operator=(const ArrayDeque& other) = default;

    bool clear() override { this->len = 0; this->front = 0; this->back = 0; return arr.clearLen(); }

    class Iter
    {
    private:
        const Arr<T>&   arr;
        ulong           index;

    public:
        Iter(const Arr<T>& a, const ulong i = ULONG_NONE) : arr(a) { i = (i == ULONG_NONE ? this->front : i);  }

        T& operator*() { return arr[index]; }
        Iter& operator++() { if (index < this->len) index++; return *this; }
        Iter operator++(int) { Iter i(index); if (index < this->len) index++; return i; }
        Iter& operator--() { if (index > 0) index--; return *this; }
        Iter operator--(int) { Iter i(index); if (index > 0) index--; return i; }
        bool operator==(const Iter& other) { return index == other.index ? TRUE : FALSE; }
        bool operator!=(const Iter& other) { return index != other.index ? TRUE : FALSE; }

        bool hasNext() const override { return index == this->back ? FALSE : TRUE; }
        Iter& next() override { return *(this++); }

    };

    Iter iter() const override { return Iter(arr); };
    Iter begin() const override { return Iter(arr); };
    Iter end() const override { return Iter(arr, this->back); };

    bool enqueue(const T& d) override { return push_back(d); };
    bool dequeue() override { return pop_front(); };
    bool peek() override { return peek_front(); };

    bool push_front(const T& d);
    bool pop_front();
    bool peek_front();
    bool push_back(const T& d);
    bool pop_back();
    bool peek_back();

};

template <typename T>
bool ArrayDeque<T>::push_front(const T& d)
{
    if (this->len == this->size)
        return FALSE;
    
}



#endif // QUEUE_H
