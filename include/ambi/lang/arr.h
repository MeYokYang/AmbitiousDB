#ifndef AMBI_ARR_H
#define AMBI_ARR_H

#include "standard.h"

namespace ambi {


#define     _arr_size_t             ulong

template <typename T, _arr_size_t MAX_LEN>
class Arr {
private:
    T                   data[MAX_LEN];

public:
    Arr() = default;
    Arr(const Arr& other) = default;
    Arr& operator=(const Arr& other) = default;
    ~Arr() = default;

    boolean empty() const { return MAX_LEN == 0 ? TRUE : FALSE; }
    _arr_size_t size() const { return MAX_LEN; }
    _arr_size_t max_size() const { return MAX_LEN; }

    T& operator[](_arr_size_t index) { return data[index]; }
    const T& operator[](_arr_size_t index) const { return data[index]; }
    T& at(_arr_size_t index);
    const T& at(_arr_size_t index) const;
    T& front() { return data[0]; }
    const T& front() const { return data[0]; }
    T& back() { return data[MAX_LEN - 1]; }
    const T& back() const { return data[MAX_LEN - 1]; }
    T* data() { return data; }
    const T* data() const { return data; }

    Arr<T, MAX_LEN>& fill(const T& value);
    Arr<T, MAX_LEN>& swap(Arr& other);

};

template <typename T, _arr_size_t MAX_LEN>
T& Arr<T, MAX_LEN>::at(_arr_size_t index) {
    if (index >= MAX_LEN) {
        // TODO throw exception
    }
    return data[index];
}

template <typename T, _arr_size_t MAX_LEN>
const T& Arr<T, MAX_LEN>::at(_arr_size_t index) const {
    if (index >= MAX_LEN) {
        // TODO throw exception
    }
    return data[index];
}

template <typename T, _arr_size_t MAX_LEN>
Arr<T, MAX_LEN>& Arr<T, MAX_LEN>::fill(const T& value) {
    for (_arr_size_t i = 0; i < MAX_LEN; ++i)
        data[i] = value;
    return *this;
}

template <typename T, _arr_size_t MAX_LEN>
Arr<T, MAX_LEN>& Arr<T, MAX_LEN>::swap(Arr& other) {
    SWAP(data, other.data);
    return *this;
}


} // namespace ambi

#endif // AMBI_ARR_H
