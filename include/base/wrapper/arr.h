#ifndef ARR_H
#define ARR_H

#include "standard.h"

template<typename T>
class Arr
{
private:
    /* data */
    static const ulong MAX_LEN = ULONG_MAX;
    ulong capacity;
    ulong len;
    T* data;

    bool resize(ulong new_capacity);

public:
    Arr(ulong len = 16);
    ~Arr() { delete[] data; };
    Arr(const Arr& other);
    Arr& operator=(const Arr& other);

    ulong length() const { return len; }
    T& operator[](ulong index);
    const T& operator[](ulong index) const;
    bool reverse();
};

template<typename T>
bool Arr<T>::resize(ulong new_capacity)
{
    if (new_capacity > MAX_LEN)
        return FALSE;

    T* new_data = new T[new_capacity];
    for (ulong i = 0; i < len; ++i)
        new_data[i] = data[i];

    delete[] data;
    data = new_data;
    capacity = new_capacity;
    return TRUE;
}

template<typename T>
Arr<T>::Arr(ulong l)
{
    if (l > MAX_LEN) {
        return; // Handle error, maybe throw an exception
    }

    if (l == 0) {
        capacity = 0;
        data = NULL;
    } else {
        if (l > MAX_LEN >> 1)
            capacity = MAX_LEN;
        else
        {
            capacity = 1;
            while (capacity < l) capacity <<= 1;
        }

        data = new T[capacity];
    }

    len = 0;
}

template<typename T>
Arr<T>::Arr(const Arr& other)
{
    capacity = other.capacity;
    len = other.len;
    data = new T[capacity];
    for (ulong i = 0; i < len; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
Arr<T>& Arr<T>::operator=(const Arr& other)
{
    if (this == &other)
        return *this;

    delete[] data;
    capacity = other.capacity;
    len = other.len;
    data = new T[capacity];
    for (ulong i = 0; i < len; ++i)
        data[i] = other.data[i];
    return *this;
}

template<typename T>
T& Arr<T>::operator[](ulong index)
{
    if (index >= len) {
        // Handle out-of-bounds access, maybe throw an exception
    }
    return data[index];
}

template<typename T>
const T& Arr<T>::operator[](ulong index) const
{
    if (index >= len) {
        // Handle out-of-bounds access, maybe throw an exception
    }
    return data[index]; 
}

template<typename T>
bool Arr<T>::reverse()
{
    for (ulong i = 0; i < len / 2; ++i) {
        T temp = data[i];
        data[i] = data[len - 1 - i];
        data[len - 1 - i] = temp;
    }
    return TRUE;
}

#endif // ARR_H
