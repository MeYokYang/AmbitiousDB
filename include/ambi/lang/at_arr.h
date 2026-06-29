#ifndef AT_ARR_H
#define AT_ARR_H

#include "ambi/mem/at_pool.h"
#include "ambi/mem/at_mem.h"

namespace atdb {


template <typename T, typename size_t = atuint>
class Arr {
private:
    MemPool<>           pool;
    static const size_t MAX_LEN = TYPE_MAX(size_t);
    static const size_t NONE_LEN = TYPE_NONE(size_t);
    T*                  data;
    size_t              len;
    size_t              cap;

public:
    // ctor
    Arr(MemPool<> p) : pool(p), data(NULL), len(0), cap(0) {};
    Arr(const Arr<T, size_t>& s, MemPool<> p);
    Arr(Arr<T, size_t>&& s) noexcept;
    Arr(const Arr<T, size_t>& s, size_t pos, size_t n, MemPool<> p);
    Arr(const T* s, size_t n, MemPool<> p);
    Arr(size_t s, const T& c, MemPool<> p);
    ~Arr();

    // value
    Arr& operator=(const Arr<T, size_t>& s);
    Arr& operator=(Arr<T, size_t>&& s) noexcept;

    // visit
    T& operator[](size_t pos) { return data[pos]; }
    const T& operator[](size_t pos) const { return data[pos]; }
    T& at(size_t pos);
    const T& at(size_t pos) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* data_ptr();
    const T* data_ptr() const;

    // capacity
    atbool empty() const noexcept { return 0 == len; }
    size_t size() const noexcept { return len; }
    size_t max_size() const noexcept { return MAX_LEN; }
    atvoid reserve(size_t n = 0);
    size_t capacity() const noexcept { return cap; }
    atvoid shrink_to_fit();

    // clear
    atvoid clear() noexcept;

    // insert
    Arr<T, size_t>& insert(size_t pos, const Arr<T, size_t>& s);
    Arr<T, size_t>& insert(size_t pos, const Arr<T, size_t>& s, size_t subpos, size_t subn);
    Arr<T, size_t>& insert(size_t pos, const T* s, size_t n);
    Arr<T, size_t>& insert(size_t pos, size_t n, const T& c);

    // erase
    Arr<T, size_t>& erase(size_t pos = 0, size_t n = NONE_LEN);

    // push_back / pop_back
    atvoid push_back(const T& c);
    atvoid pop_back();

    // assign
    Arr<T, size_t>& assign(const Arr<T, size_t>& s);
    Arr<T, size_t>& assign(Arr<T, size_t>&& s) noexcept;
    Arr<T, size_t>& assign(const Arr<T, size_t>& s, size_t subpos, size_t subn);
    Arr<T, size_t>& assign(const T* s, size_t n);
    Arr<T, size_t>& assign(size_t n, const T& c);

    // swap
    atvoid swap(Arr<T, size_t>& s) noexcept;

    // resize
    atvoid resize(size_t n);
    atvoid resize(size_t n, const T& c);

    // find
    size_t find(const T& c, size_t pos = 0) const;

    // friend
    friend atbool operator==(const Arr<T, size_t>& s1, const Arr<T, size_t>& s2);
    friend atbool operator!=(const Arr<T, size_t>& s1, const Arr<T, size_t>& s2);
    friend atvoid swap(Arr<T, size_t>& s1, Arr<T, size_t>& s2);
};

template <typename T, typename size_t>
Arr<T, size_t>::Arr(const Arr<T, size_t>& s, MemPool<> p) {
    pool = p;

    if (0 == s.len) {
        len     = 0;
        cap     = 0;
        data    = NULL;
    } else {
        at_assert(NULL != s.data);

        len     = s.len;
        cap     = s.len;
        data    = NULL;

        try {
            data = (T*)pool.alloc(sizeof(T) * s.len);
            at_memcpy((atbyte*)data, sizeof(T) * len, (atbyte*)s.data, sizeof(T) * s.len);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
Arr<T, size_t>::Arr(Arr<T, size_t>&& s) noexcept {
    pool    = s.pool;
    data    = s.data;
    len     = s.len;
    cap     = s.cap;

    s.data  = NULL;
    s.len   = 0;
    s.cap   = 0;
}

template <typename T, typename size_t>
Arr<T, size_t>::Arr(const Arr<T, size_t>& s, size_t pos, size_t n, MemPool<> p) {
    pool = p;

    if (pos >= s.len) {
        len = 0;
        cap = 0;
        data = NULL;
        return;
    }

    size_t copyLen = s.len - pos;
    if (n != NONE_LEN && n < copyLen)
        copyLen = n;

    len = copyLen;
    cap = copyLen;
    data = NULL;

    if (copyLen > 0) {
        try {
            data = (T*)pool.alloc(sizeof(T) * copyLen);
            at_memcpy((atbyte*)data, sizeof(T) * copyLen, (atbyte*)(s.data + pos), sizeof(T) * copyLen);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
Arr<T, size_t>::Arr(const T* s, size_t n, MemPool<> p) {
    pool = p;

    if (NULL == s || 0 == n) {
        len     = 0;
        cap     = 0;
        data    = NULL;
    } else {
        len     = n;
        cap     = n;

        try {
            data = (T*)pool.alloc(sizeof(T) * len);
            at_memcpy((atbyte*)data, sizeof(T) * len, (atbyte*)s, sizeof(T) * len);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
Arr<T, size_t>::Arr(size_t s, const T& c, MemPool<> p) {
    pool = p;

    if (0 == s) {
        len     = 0;
        cap     = 0;
        data    = NULL;
    } else {
        len     = s;
        cap     = s;

        try {
            data = (T*)pool.alloc(sizeof(T) * len);

            for (size_t i = 0; i < len; i++)
                data[i] = c;
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
Arr<T, size_t>::~Arr() {
    if (data != NULL) {
        pool.free((atbyte*)data);
        data = NULL;
    }
    len = 0;
    cap = 0;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::operator=(const Arr<T, size_t>& s) {

    if (this == &s)
        return *this;

    pool.free((atbyte*)data);

    len = s.len;
    cap = s.cap;
    data = NULL;

    if (cap > 0) {
        try {
            data = (T*)pool.alloc(sizeof(T) * cap);
            at_memcpy((atbyte*)data, sizeof(T) * cap, (atbyte*)s.data, sizeof(T) * s.cap);
        } catch (Code c) {
            throw c;
        }
    }

    return *this;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::operator=(Arr<T, size_t>&& s) noexcept {
    if (this == &s)
        return *this;

    pool.free((atbyte*)data);
    data    = s.data;
    len     = s.len;
    cap     = s.cap;

    s.data  = NULL;
    s.len   = 0;
    s.cap   = 0;

    return *this;
}

template <typename T, typename size_t>
T& Arr<T, size_t>::at(size_t pos) {
    if (pos >= len)
        throw Code::OUT_OF_RANGE;
    return data[pos];
}

template <typename T, typename size_t>
const T& Arr<T, size_t>::at(size_t pos) const {
    if (pos >= len)
        throw Code::OUT_OF_RANGE;
    return data[pos];
}

template <typename T, typename size_t>
T& Arr<T, size_t>::front() {
    at_assert(len > 0);
    return data[0];
}

template <typename T, typename size_t>
const T& Arr<T, size_t>::front() const {
    at_assert(len > 0);
    return data[0];
}

template <typename T, typename size_t>
T& Arr<T, size_t>::back() {
    at_assert(len > 0);
    return data[len - 1];
}

template <typename T, typename size_t>
const T& Arr<T, size_t>::back() const {
    at_assert(len > 0);
    return data[len - 1];
}

template <typename T, typename size_t>
T* Arr<T, size_t>::data_ptr() {
    return data;
}

template <typename T, typename size_t>
const T* Arr<T, size_t>::data_ptr() const {
    return data;
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::reserve(size_t n) {
    if (n > cap) {
        T* newData = NULL;

        try {
            newData = (T*)pool.alloc(sizeof(T) * n);
        } catch (Code c) {
            throw c;
        }

        if (data != NULL) {
            if (len > 0)
                at_memcpy((atbyte*)newData, sizeof(T) * n, (atbyte*)data, sizeof(T) * len);
            pool.free((atbyte*)data);
        }

        data = newData;
        cap = n;
    }
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::shrink_to_fit() {
    if (cap > len) {
        if (0 == len) {
            if (data != NULL)
                pool.free((atbyte*)data);
            data = NULL;
            cap = 0;
        } else {
            T* newData = NULL;

            try {
                newData = (T*)pool.alloc(sizeof(T) * len);
            } catch (Code c) {
                throw c;
            }

            at_memcpy((atbyte*)newData, sizeof(T) * len, (atbyte*)data, sizeof(T) * len);
            pool.free((atbyte*)data);
            data = newData;
            cap = len;
        }
    }
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::clear() noexcept {
    len = 0;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::insert(size_t pos, const Arr<T, size_t>& s) {
    return insert(pos, s, 0, NONE_LEN);
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::insert(size_t pos, const Arr<T, size_t>& s, size_t subpos, size_t subn) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    size_t copyLen = 0;
    if (subpos < s.len) {
        copyLen = s.len - subpos;
        if (subn != NONE_LEN && subn < copyLen)
            copyLen = subn;
    }

    if (0 == copyLen)
        return *this;

    size_t newLen = len + copyLen;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newData = NULL;
    try {
        newData = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (data != NULL && pos > 0)
        at_memcpy((atbyte*)newData, sizeof(T) * pos, (atbyte*)data, sizeof(T) * pos);

    at_memcpy((atbyte*)(newData + pos), sizeof(T) * copyLen, (atbyte*)(s.data + subpos), sizeof(T) * copyLen);

    if (data != NULL && pos < len)
        at_memcpy((atbyte*)(newData + pos + copyLen), sizeof(T) * (len - pos), (atbyte*)(data + pos), sizeof(T) * (len - pos));

    if (data != NULL)
        pool.free((atbyte*)data);

    data = newData;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::insert(size_t pos, const T* s, size_t n) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    if (NULL == s || 0 == n)
        return *this;

    size_t newLen = len + n;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newData = NULL;
    try {
        newData = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (data != NULL && pos > 0)
        at_memcpy((atbyte*)newData, sizeof(T) * pos, (atbyte*)data, sizeof(T) * pos);

    at_memcpy((atbyte*)(newData + pos), sizeof(T) * n, (atbyte*)s, sizeof(T) * n);

    if (data != NULL && pos < len)
        at_memcpy((atbyte*)(newData + pos + n), sizeof(T) * (len - pos), (atbyte*)(data + pos), sizeof(T) * (len - pos));

    if (data != NULL)
        pool.free((atbyte*)data);

    data = newData;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::insert(size_t pos, size_t n, const T& c) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    if (0 == n)
        return *this;

    size_t newLen = len + n;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newData = NULL;
    try {
        newData = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (data != NULL && pos > 0)
        at_memcpy((atbyte*)newData, sizeof(T) * pos, (atbyte*)data, sizeof(T) * pos);

    for (size_t i = 0; i < n; i++)
        newData[pos + i] = c;

    if (data != NULL && pos < len)
        at_memcpy((atbyte*)(newData + pos + n), sizeof(T) * (len - pos), (atbyte*)(data + pos), sizeof(T) * (len - pos));

    if (data != NULL)
        pool.free((atbyte*)data);

    data = newData;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::erase(size_t pos, size_t n) {
    if (pos >= len)
        throw Code::OUT_OF_RANGE;

    size_t eraseLen = len - pos;
    if (n != NONE_LEN && n < eraseLen)
        eraseLen = n;

    if (0 == eraseLen)
        return *this;

    size_t newLen = len - eraseLen;

    if (newLen > 0) {
        T* newData = NULL;
        try {
            newData = (T*)pool.alloc(sizeof(T) * newLen);
        } catch (Code c) {
            throw c;
        }

        if (pos > 0)
            at_memcpy((atbyte*)newData, sizeof(T) * pos, (atbyte*)data, sizeof(T) * pos);

        if (pos + eraseLen < len)
            at_memcpy((atbyte*)(newData + pos), sizeof(T) * (len - pos - eraseLen), (atbyte*)(data + pos + eraseLen), sizeof(T) * (len - pos - eraseLen));

        pool.free((atbyte*)data);
        data = newData;
        cap = newLen;
    } else {
        pool.free((atbyte*)data);
        data = NULL;
        cap = 0;
    }

    len = newLen;

    return *this;
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::push_back(const T& c) {
    size_t newLen = len + 1;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newData = NULL;
    try {
        newData = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (data != NULL && len > 0)
        at_memcpy((atbyte*)newData, sizeof(T) * len, (atbyte*)data, sizeof(T) * len);

    newData[len] = c;

    if (data != NULL)
        pool.free((atbyte*)data);

    data = newData;
    len = newLen;
    cap = newCap;
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::pop_back() {
    at_assert(len > 0);
    len--;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::assign(const Arr<T, size_t>& s) {
    return operator=(s);
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::assign(Arr<T, size_t>&& s) noexcept {
    return operator=(static_cast<Arr<T, size_t>&&>(s));
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::assign(const Arr<T, size_t>& s, size_t subpos, size_t subn) {
    pool.free((atbyte*)data);

    if (subpos >= s.len) {
        len = 0;
        cap = 0;
        data = NULL;
        return *this;
    }

    size_t copyLen = s.len - subpos;
    if (subn != NONE_LEN && subn < copyLen)
        copyLen = subn;

    len = copyLen;
    cap = copyLen;
    data = NULL;

    if (copyLen > 0) {
        try {
            data = (T*)pool.alloc(sizeof(T) * copyLen);
            at_memcpy((atbyte*)data, sizeof(T) * copyLen, (atbyte*)(s.data + subpos), sizeof(T) * copyLen);
        } catch (Code c) {
            throw c;
        }
    }

    return *this;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::assign(const T* s, size_t n) {
    pool.free((atbyte*)data);

    if (NULL == s || 0 == n) {
        len = 0;
        cap = 0;
        data = NULL;
        return *this;
    }

    len = n;
    cap = n;

    try {
        data = (T*)pool.alloc(sizeof(T) * n);
        at_memcpy((atbyte*)data, sizeof(T) * n, (atbyte*)s, sizeof(T) * n);
    } catch (Code c) {
        throw c;
    }

    return *this;
}

template <typename T, typename size_t>
Arr<T, size_t>& Arr<T, size_t>::assign(size_t n, const T& c) {
    pool.free((atbyte*)data);

    if (0 == n) {
        len = 0;
        cap = 0;
        data = NULL;
        return *this;
    }

    len = n;
    cap = n;

    try {
        data = (T*)pool.alloc(sizeof(T) * n);
        for (size_t i = 0; i < n; i++)
            data[i] = c;
    } catch (Code c) {
        throw c;
    }

    return *this;
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::swap(Arr<T, size_t>& s) noexcept {
    MemPool<> tmpPool = pool;
    T* tmpData = data;
    size_t tmpLen = len;
    size_t tmpCap = cap;

    pool = s.pool;
    data = s.data;
    len  = s.len;
    cap  = s.cap;

    s.pool = tmpPool;
    s.data = tmpData;
    s.len  = tmpLen;
    s.cap  = tmpCap;
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::resize(size_t n) {
    if (n > len) {
        size_t oldLen = len;
        reserve(n);
        for (size_t i = oldLen; i < n; i++)
            data[i] = T();
    }
    len = n;
}

template <typename T, typename size_t>
atvoid Arr<T, size_t>::resize(size_t n, const T& c) {
    if (n > len) {
        size_t oldLen = len;
        reserve(n);
        for (size_t i = oldLen; i < n; i++)
            data[i] = c;
    }
    len = n;
}

template <typename T, typename size_t>
size_t Arr<T, size_t>::find(const T& c, size_t pos) const {
    if (pos >= len)
        return NONE_LEN;

    for (size_t i = pos; i < len; i++) {
        if (data[i] == c)
            return i;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
atbool operator==(const Arr<T, size_t>& s1, const Arr<T, size_t>& s2) {
    if (s1.len != s2.len)
        return FALSE;

    for (size_t i = 0; i < s1.len; i++) {
        if (s1.data[i] != s2.data[i])
            return FALSE;
    }

    return TRUE;
}

template <typename T, typename size_t>
atbool operator!=(const Arr<T, size_t>& s1, const Arr<T, size_t>& s2) {
    return !(s1 == s2);
}

template <typename T, typename size_t>
atvoid swap(Arr<T, size_t>& s1, Arr<T, size_t>& s2) {
    s1.swap(s2);
}


} // end namespace atdb

#endif // AT_ARR_H
