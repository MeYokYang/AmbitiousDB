#ifndef AMBI_VEC_H
#define AMBI_VEC_H

#include "standard.h"

namespace ambi {


#define     _vec_size_t         ulong
#define     _vec_max_len        get_type_max(_vec_size_t)

template <typename T>
class Vec
{
private:
    static const _vec_size_t    MAX_LEN = _vec_max_len;
    _vec_size_t                 capacity;
    _vec_size_t                 len;
    T*                          data;

public:
    // ctor
    Vec() : capacity(0), len(0), data(NULL) {}
    Vec(_vec_size_t l);
    Vec(_vec_size_t l, const T& value);
    //Vec(InputIt first, InputIt last);
    Vec(const Vec& other);
    //Vec(const Vec&& other);
    //Vec(std::initializer_list<T> init);
    Vec& operator=(const Vec& other);
    ~Vec();

    // iter
    // TODO

    // capacity
    boolean empty() const { return len == 0 ? TRUE : FALSE; }
    _vec_size_t size() const { return len; }
    _vec_size_t capacity() const { return capacity; }
    boolean reserve(_vec_size_t l);
    boolean shrink_to_fit();
    Vec& resize(_vec_size_t l);
    Vec& resize(_vec_size_t l, const T& value);

    // access
    T& operator[](_vec_size_t index) { return data[index]; }
    const T& operator[](_vec_size_t index) const { return data[index]; }
    T& at(_vec_size_t index);
    const T& at(_vec_size_t index) const;
    T& front() { return data[0]; }
    const T& front() const { return data[0]; }
    T& back() { return data[len - 1]; }
    const T& back() const { return data[len - 1]; }
    T* data() { return data; }
    const T* data() const { return data; }

    // modifiers
    Vec<T>& assign(_vec_size_t l, const T& value);
    //Vec<T>& assign(InputIt first, InputIt last);
    //Vec<T>& assign(std::initializer_list<T> init);
    Vec<T>& push_back(const T& value);
    //Vec<T>& emplace_back(Args&&... value);
    Vec<T>& pop_back();
    //Vec<T>& insert(iterator pos, const T& value);
    //Vec<T>& insert(iterator pos, _vec_size_t n, const T& value);
    //Vec<T>& insert(iterator pos, InputIt first, InputIt last);
    //Vec<T>& emplace(iterator pos, Args&&... value);
    //Vec<T>& erase(iterator pos);
    //Vec<T>& erase(iterator first, iterator last);
    Vec<T>& clear();
    Vec<T>& swap(Vec& other);

    // allocator
    //get_allocator();

    // non-member functions
    // TODO

};

template <typename T>
Vec<T>::Vec(_vec_size_t l) : capacity(l), len(l), data(new T[l]) {}

template <typename T>
Vec<T>::Vec(_vec_size_t l, const T& value) : capacity(l), len(l), data(new T[l]) { assign(l, value); }

template <typename T>
Vec<T>::Vec(const Vec& other) : capacity(other.capacity), len(other.len), data(new T[other.capacity]) {
    for (_vec_size_t i = 0; i < len; ++i)
        data[i] = other.data[i];
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& other) {
    if (this == &other)
        return *this;

    delete[] data;
    capacity = other.capacity;
    len = other.len;
    data = new T[capacity];
    for (_vec_size_t i = 0; i < len; ++i)
        data[i] = other.data[i];
    return *this;
}

template <typename T>
Vec<T>::~Vec() { delete[] data; }

template <typename T>
boolean Vec<T>::reserve(_vec_size_t l) {
    if (l > capacity) {
        _vec_size_t new_capacity = l;
        if (capacity > (MAX_LEN >> 1))
            new_capacity = MAX_LEN;
        else {
            while (new_capacity < l) new_capacity <<= 1;    // double increase capacity
        }

        T* new_data = new T[new_capacity];
        for (_vec_size_t i = 0; i < len; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = new_capacity;
        return TRUE;
    }
    return FALSE;
}

template <typename T>
boolean Vec<T>::shrink_to_fit() {
    if (capacity > len) {
        T* new_data = new T[len];
        for (_vec_size_t i = 0; i < len; ++i)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
        capacity = len;
        return TRUE;
    }
    return FALSE;
}

template <typename T>
Vec<T>& Vec<T>::resize(_vec_size_t l) {
    if (l > capacity)
        reserve(l);
    len = l;
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::resize(_vec_size_t l, const T& value) {
    if (l > capacity)
        reserve(l);
    len = l;
    for (_vec_size_t i = 0; i < len; ++i)
        data[i] = value;
    return *this;
}

template <typename T>
T& Vec<T>::at(_vec_size_t index) {
    if (index >= len) {
        // TODO throw exception
    }
    return data[index];
}

template <typename T>
const T& Vec<T>::at(_vec_size_t index) const {
    if (index >= len) {
        // TODO throw exception
    }
    return data[index];
}

template <typename T>
Vec<T>& Vec<T>::assign(_vec_size_t l, const T& value) {
    if (l > capacity)
        reserve(l);
    len = l;
    for (_vec_size_t i = 0; i < len; ++i)
        data[i] = value;
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::push_back(const T& value) {
    if (len == capacity)
        reserve(capacity + 1);
    data[len++] = value;
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::pop_back() {
    if (len == 0)
        return FALSE;
    --len;
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::clear() {
    len = 0;
    return *this;
}

template <typename T>
Vec<T>& Vec<T>::swap(Vec& other) {
    SWAP(capacity, other.capacity);
    SWAP(len, other.len);
    SWAP(data, other.data);
    return *this;
}


} // namespace ambi

#endif // AMBI_VEC_H
