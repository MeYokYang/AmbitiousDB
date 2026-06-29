#ifndef AT_STR_H
#define AT_STR_H

#include "ambi/mem/at_pool.h"
#include "ambi/lang/at_character.h"
#include "ambi/mem/at_mem.h"

namespace atdb {


#define Str                 BaseStr<atchar, atuint>

template <typename T = atchar, typename size_t = atuint>
class BaseStr {
private:
    MemPool<>           pool;
    static const size_t MAX_LEN = TYPE_MAX(size_t);
    static const size_t NONE_LEN = TYPE_NONE(size_t);
    T*                  str;
    size_t              len;
    size_t              cap;

public:
    // ctor
    BaseStr(MemPool<> p = getStringPool()) : pool(p), str(NULL), len(0), cap(0) {};
    BaseStr(const BaseStr<T, size_t>& s, MemPool<> p = getStringPool());
    BaseStr(BaseStr<T, size_t>&& s) noexcept;
    BaseStr(const BaseStr<T, size_t>& s, size_t pos, size_t n = NONE_LEN, MemPool<> p = getStringPool());
    BaseStr(const T* s, MemPool<> p = getStringPool());
    BaseStr(const T* s, size_t n, MemPool<> p = getStringPool());
    BaseStr(size_t s, T c, MemPool<> p = getStringPool());
    // TODO iter
    ~BaseStr();
    
    // value
    BaseStr& operator=(const BaseStr<T, size_t>& s);
    BaseStr& operator=(BaseStr<T, size_t>&& s) noexcept;
    BaseStr& operator=(const T* s);
    BaseStr& operator=(T c);

    // visit
    T& operator[](size_t pos) { return str[pos]; } // NO THROW
    const T& operator[](size_t pos) const { return str[pos]; }
    T& at(size_t pos); // THROW
    const T& at(size_t pos) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    const T* c_str() const;
    const T* data() const;
    T* data();

    // TODO iter

    // capacity
    atbool empty() const noexcept { return 0 == len; }
    size_t size() const noexcept { return len; }
    size_t length() const noexcept { return len; }
    size_t max_size() const noexcept { return MAX_LEN; }
    atvoid reserve(size_t n = 0);
    size_t capacity() const noexcept { return cap; }
    atvoid shrink_to_fit();

    // clear
    atvoid clear() noexcept;

    // insert
    BaseStr<T, size_t>& insert(size_t pos, const BaseStr<T, size_t>& s);
    BaseStr<T, size_t>& insert(size_t pos, const BaseStr<T, size_t>& s, size_t subpos, size_t subn);
    BaseStr<T, size_t>& insert(size_t pos, const T* s);
    BaseStr<T, size_t>& insert(size_t pos, const T* s, size_t n);
    BaseStr<T, size_t>& insert(size_t pos, size_t n, T c);
    // TODO iter

    // erase
    BaseStr<T, size_t>& erase(size_t pos = 0, size_t n = NONE_LEN);
    // TODO iter

    // append
    BaseStr<T, size_t>& operator+=(const BaseStr<T, size_t> s);
    BaseStr<T, size_t>& operator+=(const T* s);
    BaseStr<T, size_t>& operator+=(T c);
    BaseStr<T, size_t>& append(const BaseStr<T, size_t> s);
    BaseStr<T, size_t>& append(const BaseStr<T, size_t> s, size_t subpos, size_t subn);
    BaseStr<T, size_t>& append(const T* s);
    BaseStr<T, size_t>& append(const T* s, size_t n);
    BaseStr<T, size_t>& append(size_t n, T c);
    atvoid push_back(T c);

    // assign
    BaseStr<T, size_t>& assign(const BaseStr<T, size_t>& s);
    BaseStr<T, size_t>& assign(BaseStr<T, size_t>&& s) noexcept;
    BaseStr<T, size_t>& assign(const BaseStr<T, size_t>& s, size_t subpos, size_t subn);
    BaseStr<T, size_t>& assign(const T* s);
    BaseStr<T, size_t>& assign(const T* s, size_t n);
    BaseStr<T, size_t>& assign(size_t n, T c);

    // replace
    BaseStr<T, size_t>& replace(size_t pos, size_t len, const BaseStr<T, size_t>& s);
    BaseStr<T, size_t>& replace(size_t pos, size_t len, const BaseStr<T, size_t>& s, size_t subpos, size_t subn);
    BaseStr<T, size_t>& replace(size_t pos, size_t len, const T* s);
    BaseStr<T, size_t>& replace(size_t pos, size_t len, const T* s, size_t n);
    BaseStr<T, size_t>& replace(size_t pos, size_t len, size_t n, T c);

    // swap
    atvoid swap(BaseStr<T, size_t>& s) noexcept;

    // resize
    atvoid pop_back();
    atvoid resize(size_t n);
    atvoid resize(size_t n, T c);


    // find
    size_t find(const BaseStr<T, size_t>& s, size_t pos = 0) const;
    size_t find(const T* s, size_t pos = 0) const;
    size_t find(const T* s, size_t pos, size_t n) const;
    size_t find(T c, size_t pos = 0) const;
    size_t rfind(const BaseStr<T, size_t>& s, size_t pos = NONE_LEN) const;
    size_t rfind(const T* s, size_t pos = NONE_LEN) const;
    size_t rfind(const T* s, size_t pos, size_t n) const;
    size_t rfind(T c, size_t pos = NONE_LEN) const;

    size_t find_first_of(const BaseStr<T, size_t>& s, size_t pos = 0) const;
    size_t find_first_of(const T* s, size_t pos = 0) const;
    size_t find_first_of(const T* s, size_t pos, size_t n) const;
    size_t find_first_of(T c, size_t pos = 0) const;
    size_t find_first_not_of(const BaseStr<T, size_t>& s, size_t pos = 0) const;
    size_t find_first_not_of(const T* s, size_t pos = 0) const;
    size_t find_first_not_of(const T* s, size_t pos, size_t n) const;
    size_t find_first_not_of(T c, size_t pos = 0) const;
    size_t find_last_of(const BaseStr<T, size_t>& s, size_t pos = NONE_LEN) const;
    size_t find_last_of(const T* s, size_t pos = NONE_LEN) const;
    size_t find_last_of(const T* s, size_t pos, size_t n) const;
    size_t find_last_of(T c, size_t pos = NONE_LEN) const;
    size_t find_last_not_of(const BaseStr<T, size_t>& s, size_t pos = NONE_LEN) const;
    size_t find_last_not_of(const T* s, size_t pos = NONE_LEN) const;
    size_t find_last_not_of(const T* s, size_t pos, size_t n) const;
    size_t find_last_not_of(T c, size_t pos = NONE_LEN) const;

    // substr
    const BaseStr<T, size_t> substr(size_t pos = 0, size_t n = NONE_LEN) const;

    // compare
    atbool compare(const BaseStr<T, size_t>& s) const;
    atbool compare(size_t pos, size_t n, const BaseStr<T, size_t>& s) const;
    atbool compare(size_t pos, size_t n, const BaseStr<T, size_t>& s, size_t subpos, size_t subn) const;
    atbool compare(const T* s) const;
    atbool compare(size_t pos, size_t n, const T* s) const;
    atbool compare(size_t pos, size_t n, const T* s, size_t subpos, size_t subn) const;

    // convert
    static atint stoi(const BaseStr<T, size_t>& s, size_t* pos = NULL, atint base = 10);
    static atlong stol(const BaseStr<T, size_t>& s, size_t* pos = NULL, atint base = 10);
    static atulong stoul(const BaseStr<T, size_t>& s, size_t* pos = NULL, atint base = 10);
    static atfloat stof(const BaseStr<T, size_t>& s, size_t* pos = NULL, atint base = 10);
    static atdouble stod(const BaseStr<T, size_t>& s, size_t* pos = NULL, atint base = 10);
    static BaseStr<T, size_t> to_string(atint val);

    // friend
    friend atbool operator==(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2);
    friend atbool operator!=(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2);
    friend atbool operator<(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2);
    friend atbool operator<=(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2);
    friend atbool operator>(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2);
    friend atbool operator>=(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2);
    friend BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2);
    friend BaseStr<T, size_t> operator+(BaseStr<T, size_t>&& s1, const BaseStr<T, size_t>& s2);
    friend BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s1, BaseStr<T, size_t>&& s2);
    friend BaseStr<T, size_t> operator+(BaseStr<T, size_t>&& s1, BaseStr<T, size_t>&& s2);
    friend BaseStr<T, size_t> operator+(const T* s1, const BaseStr<T, size_t>& s2);
    friend BaseStr<T, size_t> operator+(T c, const BaseStr<T, size_t>& s);
    friend BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s, const T* c);
    friend BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s, T c);
    friend atvoid swap(BaseStr<T, size_t>& s1, BaseStr<T, size_t>& s2);
};

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(const BaseStr<T, size_t>& s, MemPool<> p) {
    pool = p;

    if (0 == s.len) {
        len     = 0;
        cap     = 0;
        str     = NULL;
    } else {
        at_assert(NULL != s.str);

        len     = s.len;
        cap     = s.len;
        str     = NULL;

        try {
            str = (T*)pool.alloc(sizeof(T) * s.len);
            at_memcpy((atbyte*)str, sizeof(T) * len, (atbyte*)s.str, sizeof(T) * s.len);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(BaseStr<T, size_t>&& s) noexcept {
    pool    = s.p;
    len     = s.len;
    cap     = s.cap;
    str     = s.str;

    s.len   = 0;
    s.cap   = 0;
    s.str   = NULL;
}

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(const BaseStr<T, size_t>& s, size_t pos, size_t n, MemPool<> p) {
    pool = p;

    if (pos >= s.len) {
        len = 0;
        cap = 0;
        str = NULL;
        return;
    }

    size_t copyLen = s.len - pos;
    if (n != NONE_LEN && n < copyLen)
        copyLen = n;

    len = copyLen;
    cap = copyLen;
    str = NULL;

    if (copyLen > 0) {
        try {
            str = (T*)pool.alloc(sizeof(T) * copyLen);
            at_memcpy((atbyte*)str, sizeof(T) * copyLen, (atbyte*)(s.str + pos), sizeof(T) * copyLen);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(const T* s, MemPool<> p) {
    pool = p;

    if (NULL == s) {
        len     = 0;
        cap     = 0;
        str     = NULL;
    } else {
        len     = Character<T, size_t>::strlen(s);
        cap     = len;

        try {
            str = (T*)pool.alloc(sizeof(T) * len);
            at_memcpy((atbyte*)str, sizeof(T) * len, (atbyte*)s, sizeof(T) * len);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(const T* s, size_t n, MemPool<> p) {
    pool = p;

    if (NULL == s || 0 == n) {
        len     = 0;
        cap     = 0;
        str     = NULL;
    } else {
        len     = n;
        cap     = n;

        try {
            str = (T*)pool.alloc(sizeof(T) * len);
            at_memcpy((atbyte*)str, sizeof(T) * len, (atbyte*)s, sizeof(T) * len);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(size_t s, T c, MemPool<> p) {
    pool = p;

    if (0 == s) {
        len     = 0;
        cap     = 0;
        str     = NULL;
    } else {
        len     = s;
        cap     = s;

        try {
            str = (T*)pool.alloc(sizeof(T) * len);

            for (size_t i = 0; i < len; i++)
                str[i] = c;
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
BaseStr<T, size_t>::~BaseStr() {
    if (str != NULL) {
        pool.free((atbyte*)str);
        str = NULL;
    }
    len = 0;
    cap = 0;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::operator=(const BaseStr<T, size_t>& s) {

    if (this == &s)
        return *this;

    pool.free((atbyte*)str);

    len = s.len;
    cap = s.cap;
    str = NULL;

    if (cap > 0) {
        try {
            str = (T*)pool.alloc(sizeof(T) * cap);
            at_memcpy((atbyte*)str, sizeof(T) * cap, (atbyte*)s.str, sizeof(T) * s.cap);
        } catch (Code c) {
            throw c;
        }
    }
    
    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::operator=(BaseStr<T, size_t>&& s) noexcept {
    if (this == &s)
        return *this;

    pool.free((atbyte*)str);
    str     = s.str;
    len     = s.len;
    cap     = s.cap;

    s.str   = NULL;
    s.len   = 0;
    s.cap   = 0;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::operator=(const T* s) {
    pool.free((atbyte*)str);

    if (NULL == s) {
        len = 0;
        cap = 0;
        str = NULL;
    } else {
        len = Character<T, size_t>::strlen(s);
        cap = len;
        str = NULL;

        if (len > 0) {
            try {
                str = (T*)pool.alloc(sizeof(T) * len);
                at_memcpy((atbyte*)str, sizeof(T) * len, (atbyte*)s, sizeof(T) * len);
            } catch (Code c) {
                throw c;
            }
        }
    }

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::operator=(T c) {
    pool.free((atbyte*)str);

    len = 1;
    cap = 1;

    try {
        str = (T*)pool.alloc(sizeof(T));
        str[0] = c;
    } catch (Code c) {
        throw c;
    }

    return *this;
}

template <typename T, typename size_t>
T& BaseStr<T, size_t>::at(size_t pos) {
    if (pos >= len)
        throw Code::OUT_OF_RANGE;
    return str[pos];
}

template <typename T, typename size_t>
const T& BaseStr<T, size_t>::at(size_t pos) const {
    if (pos >= len)
        throw Code::OUT_OF_RANGE;
    return str[pos];
}

template <typename T, typename size_t>
T& BaseStr<T, size_t>::front() {
    at_assert(len > 0);
    return str[0];
}

template <typename T, typename size_t>
const T& BaseStr<T, size_t>::front() const {
    at_assert(len > 0);
    return str[0];
}

template <typename T, typename size_t>
T& BaseStr<T, size_t>::back() {
    at_assert(len > 0);
    return str[len - 1];
}

template <typename T, typename size_t>
const T& BaseStr<T, size_t>::back() const {
    at_assert(len > 0);
    return str[len - 1];
}

template <typename T, typename size_t>
const T* BaseStr<T, size_t>::c_str() const {
    return str;
}

template <typename T, typename size_t>
const T* BaseStr<T, size_t>::data() const {
    return str;
}

template <typename T, typename size_t>
T* BaseStr<T, size_t>::data() {
    return str;
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::reserve(size_t n) {
    if (n > cap) {
        T* newStr = NULL;

        try {
            newStr = (T*)pool.alloc(sizeof(T) * n);
        } catch (Code c) {
            throw c;
        }

        if (str != NULL) {
            if (len > 0)
                at_memcpy((atbyte*)newStr, sizeof(T) * n, (atbyte*)str, sizeof(T) * len);
            pool.free((atbyte*)str);
        }

        str = newStr;
        cap = n;
    }
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::shrink_to_fit() {
    if (cap > len) {
        if (0 == len) {
            if (str != NULL)
                pool.free((atbyte*)str);
            str = NULL;
            cap = 0;
        } else {
            T* newStr = NULL;

            try {
                newStr = (T*)pool.alloc(sizeof(T) * len);
            } catch (Code c) {
                throw c;
            }

            at_memcpy((atbyte*)newStr, sizeof(T) * len, (atbyte*)str, sizeof(T) * len);
            pool.free((atbyte*)str);
            str = newStr;
            cap = len;
        }
    }
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::clear() noexcept {
    len = 0;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::insert(size_t pos, const BaseStr<T, size_t>& s) {
    return insert(pos, s, 0, NONE_LEN);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::insert(size_t pos, const BaseStr<T, size_t>& s, size_t subpos, size_t subn) {
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

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && pos > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * pos, (atbyte*)str, sizeof(T) * pos);

    at_memcpy((atbyte*)(newStr + pos), sizeof(T) * copyLen, (atbyte*)(s.str + subpos), sizeof(T) * copyLen);

    if (str != NULL && pos < len)
        at_memcpy((atbyte*)(newStr + pos + copyLen), sizeof(T) * (len - pos), (atbyte*)(str + pos), sizeof(T) * (len - pos));

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::insert(size_t pos, const T* s) {
    if (NULL == s)
        return *this;

    size_t slen = Character<T, size_t>::strlen(s);
    return insert(pos, s, slen);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::insert(size_t pos, const T* s, size_t n) {
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

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && pos > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * pos, (atbyte*)str, sizeof(T) * pos);

    at_memcpy((atbyte*)(newStr + pos), sizeof(T) * n, (atbyte*)s, sizeof(T) * n);

    if (str != NULL && pos < len)
        at_memcpy((atbyte*)(newStr + pos + n), sizeof(T) * (len - pos), (atbyte*)(str + pos), sizeof(T) * (len - pos));

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::insert(size_t pos, size_t n, T c) {
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

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && pos > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * pos, (atbyte*)str, sizeof(T) * pos);

    for (size_t i = 0; i < n; i++)
        newStr[pos + i] = c;

    if (str != NULL && pos < len)
        at_memcpy((atbyte*)(newStr + pos + n), sizeof(T) * (len - pos), (atbyte*)(str + pos), sizeof(T) * (len - pos));

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::erase(size_t pos, size_t n) {
    if (pos >= len)
        throw Code::OUT_OF_RANGE;

    size_t eraseLen = len - pos;
    if (n != NONE_LEN && n < eraseLen)
        eraseLen = n;

    if (0 == eraseLen)
        return *this;

    size_t newLen = len - eraseLen;

    if (newLen > 0) {
        T* newStr = NULL;
        try {
            newStr = (T*)pool.alloc(sizeof(T) * newLen);
        } catch (Code c) {
            throw c;
        }

        if (pos > 0)
            at_memcpy((atbyte*)newStr, sizeof(T) * pos, (atbyte*)str, sizeof(T) * pos);

        if (pos + eraseLen < len)
            at_memcpy((atbyte*)(newStr + pos), sizeof(T) * (len - pos - eraseLen), (atbyte*)(str + pos + eraseLen), sizeof(T) * (len - pos - eraseLen));

        pool.free((atbyte*)str);
        str = newStr;
        cap = newLen;
    } else {
        pool.free((atbyte*)str);
        str = NULL;
        cap = 0;
    }

    len = newLen;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::operator+=(const BaseStr<T, size_t> s) {
    return append(s);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::operator+=(const T* s) {
    return append(s);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::operator+=(T c) {
    push_back(c);
    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::append(const BaseStr<T, size_t> s) {
    return append(s, 0, NONE_LEN);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::append(const BaseStr<T, size_t> s, size_t subpos, size_t subn) {
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

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && len > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * len, (atbyte*)str, sizeof(T) * len);

    at_memcpy((atbyte*)(newStr + len), sizeof(T) * copyLen, (atbyte*)(s.str + subpos), sizeof(T) * copyLen);

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::append(const T* s) {
    if (NULL == s)
        return *this;

    size_t slen = Character<T, size_t>::strlen(s);
    return append(s, slen);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::append(const T* s, size_t n) {
    if (NULL == s || 0 == n)
        return *this;

    size_t newLen = len + n;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && len > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * len, (atbyte*)str, sizeof(T) * len);

    at_memcpy((atbyte*)(newStr + len), sizeof(T) * n, (atbyte*)s, sizeof(T) * n);

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::append(size_t n, T c) {
    if (0 == n)
        return *this;

    size_t newLen = len + n;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && len > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * len, (atbyte*)str, sizeof(T) * len);

    for (size_t i = 0; i < n; i++)
        newStr[len + i] = c;

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::push_back(T c) {
    size_t newLen = len + 1;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && len > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * len, (atbyte*)str, sizeof(T) * len);

    newStr[len] = c;

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::assign(const BaseStr<T, size_t>& s) {
    return operator=(s);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::assign(BaseStr<T, size_t>&& s) noexcept {
    return operator=(static_cast<BaseStr<T, size_t>&&>(s));
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::assign(const BaseStr<T, size_t>& s, size_t subpos, size_t subn) {
    pool.free((atbyte*)str);

    if (subpos >= s.len) {
        len = 0;
        cap = 0;
        str = NULL;
        return *this;
    }

    size_t copyLen = s.len - subpos;
    if (subn != NONE_LEN && subn < copyLen)
        copyLen = subn;

    len = copyLen;
    cap = copyLen;
    str = NULL;

    if (copyLen > 0) {
        try {
            str = (T*)pool.alloc(sizeof(T) * copyLen);
            at_memcpy((atbyte*)str, sizeof(T) * copyLen, (atbyte*)(s.str + subpos), sizeof(T) * copyLen);
        } catch (Code c) {
            throw c;
        }
    }

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::assign(const T* s) {
    return operator=(s);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::assign(const T* s, size_t n) {
    pool.free((atbyte*)str);

    if (NULL == s || 0 == n) {
        len = 0;
        cap = 0;
        str = NULL;
        return *this;
    }

    len = n;
    cap = n;

    try {
        str = (T*)pool.alloc(sizeof(T) * n);
        at_memcpy((atbyte*)str, sizeof(T) * n, (atbyte*)s, sizeof(T) * n);
    } catch (Code c) {
        throw c;
    }

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::assign(size_t n, T c) {
    pool.free((atbyte*)str);

    if (0 == n) {
        len = 0;
        cap = 0;
        str = NULL;
        return *this;
    }

    len = n;
    cap = n;

    try {
        str = (T*)pool.alloc(sizeof(T) * n);
        for (size_t i = 0; i < n; i++)
            str[i] = c;
    } catch (Code c) {
        throw c;
    }

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::replace(size_t pos, size_t l, const BaseStr<T, size_t>& s) {
    return replace(pos, l, s, 0, NONE_LEN);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::replace(size_t pos, size_t l, const BaseStr<T, size_t>& s, size_t subpos, size_t subn) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    size_t oldLen = len - pos;
    if (l != NONE_LEN && l < oldLen)
        oldLen = l;

    size_t copyLen = 0;
    if (subpos < s.len) {
        copyLen = s.len - subpos;
        if (subn != NONE_LEN && subn < copyLen)
            copyLen = subn;
    }

    size_t newLen = len - oldLen + copyLen;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && pos > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * pos, (atbyte*)str, sizeof(T) * pos);

    if (copyLen > 0)
        at_memcpy((atbyte*)(newStr + pos), sizeof(T) * copyLen, (atbyte*)(s.str + subpos), sizeof(T) * copyLen);

    if (str != NULL && pos + oldLen < len)
        at_memcpy((atbyte*)(newStr + pos + copyLen), sizeof(T) * (len - pos - oldLen), (atbyte*)(str + pos + oldLen), sizeof(T) * (len - pos - oldLen));

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::replace(size_t pos, size_t l, const T* s) {
    if (NULL == s)
        return *this;

    size_t slen = Character<T, size_t>::strlen(s);
    return replace(pos, l, s, slen);
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::replace(size_t pos, size_t l, const T* s, size_t n) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    size_t oldLen = len - pos;
    if (l != NONE_LEN && l < oldLen)
        oldLen = l;

    size_t copyLen = 0;
    if (s != NULL && n > 0)
        copyLen = n;

    size_t newLen = len - oldLen + copyLen;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && pos > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * pos, (atbyte*)str, sizeof(T) * pos);

    if (copyLen > 0)
        at_memcpy((atbyte*)(newStr + pos), sizeof(T) * copyLen, (atbyte*)s, sizeof(T) * copyLen);

    if (str != NULL && pos + oldLen < len)
        at_memcpy((atbyte*)(newStr + pos + copyLen), sizeof(T) * (len - pos - oldLen), (atbyte*)(str + pos + oldLen), sizeof(T) * (len - pos - oldLen));

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
BaseStr<T, size_t>& BaseStr<T, size_t>::replace(size_t pos, size_t l, size_t n, T c) {
    if (pos > len)
        throw Code::OUT_OF_RANGE;

    size_t oldLen = len - pos;
    if (l != NONE_LEN && l < oldLen)
        oldLen = l;

    size_t newLen = len - oldLen + n;
    size_t newCap = cap;
    if (0 == newCap)
        newCap = 1;
    while (newCap < newLen)
        newCap <<= 1;

    T* newStr = NULL;
    try {
        newStr = (T*)pool.alloc(sizeof(T) * newCap);
    } catch (Code c) {
        throw c;
    }

    if (str != NULL && pos > 0)
        at_memcpy((atbyte*)newStr, sizeof(T) * pos, (atbyte*)str, sizeof(T) * pos);

    for (size_t i = 0; i < n; i++)
        newStr[pos + i] = c;

    if (str != NULL && pos + oldLen < len)
        at_memcpy((atbyte*)(newStr + pos + n), sizeof(T) * (len - pos - oldLen), (atbyte*)(str + pos + oldLen), sizeof(T) * (len - pos - oldLen));

    if (str != NULL)
        pool.free((atbyte*)str);

    str = newStr;
    len = newLen;
    cap = newCap;

    return *this;
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::swap(BaseStr<T, size_t>& s) noexcept {
    MemPool<> tmpPool = pool;
    T* tmpStr = str;
    size_t tmpLen = len;
    size_t tmpCap = cap;

    pool = s.pool;
    str  = s.str;
    len  = s.len;
    cap  = s.cap;

    s.pool = tmpPool;
    s.str  = tmpStr;
    s.len  = tmpLen;
    s.cap  = tmpCap;
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::pop_back() {
    at_assert(len > 0);
    len--;
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::resize(size_t n) {
    if (n > len) {
        reserve(n);
        for (size_t i = len; i < n; i++)
            str[i] = T();
    }
    len = n;
}

template <typename T, typename size_t>
atvoid BaseStr<T, size_t>::resize(size_t n, T c) {
    if (n > len) {
        size_t oldLen = len;
        reserve(n);
        for (size_t i = oldLen; i < n; i++)
            str[i] = c;
    }
    len = n;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find(const BaseStr<T, size_t>& s, size_t pos) const {
    if (pos >= len || 0 == s.len || s.len > len - pos)
        return NONE_LEN;

    for (size_t i = pos; i <= len - s.len; i++) {
        size_t j = 0;
        while (j < s.len && str[i + j] == s.str[j])
            j++;
        if (j == s.len)
            return i;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find(const T* s, size_t pos) const {
    if (NULL == s)
        return NONE_LEN;

    size_t slen = Character<T, size_t>::strlen(s);
    return find(s, pos, slen);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find(const T* s, size_t pos, size_t n) const {
    if (NULL == s || 0 == n || pos >= len || n > len - pos)
        return NONE_LEN;

    for (size_t i = pos; i <= len - n; i++) {
        size_t j = 0;
        while (j < n && str[i + j] == s[j])
            j++;
        if (j == n)
            return i;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find(T c, size_t pos) const {
    if (pos >= len)
        return NONE_LEN;

    for (size_t i = pos; i < len; i++) {
        if (str[i] == c)
            return i;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::rfind(const BaseStr<T, size_t>& s, size_t pos) const {
    if (0 == s.len || s.len > len)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - s.len : pos;
    if (start > len - s.len)
        start = len - s.len;

    for (size_t i = start; i != NONE_LEN; i--) {
        size_t j = 0;
        while (j < s.len && str[i + j] == s.str[j])
            j++;
        if (j == s.len)
            return i;
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::rfind(const T* s, size_t pos) const {
    if (NULL == s)
        return NONE_LEN;

    size_t slen = Character<T, size_t>::strlen(s);
    return rfind(s, pos, slen);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::rfind(const T* s, size_t pos, size_t n) const {
    if (NULL == s || 0 == n || n > len)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - n : pos;
    if (start > len - n)
        start = len - n;

    for (size_t i = start; i != NONE_LEN; i--) {
        size_t j = 0;
        while (j < n && str[i + j] == s[j])
            j++;
        if (j == n)
            return i;
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::rfind(T c, size_t pos) const {
    if (0 == len)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - 1 : pos;

    for (size_t i = start; i != NONE_LEN; i--) {
        if (str[i] == c)
            return i;
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_of(const BaseStr<T, size_t>& s, size_t pos) const {
    if (pos >= len || 0 == s.len)
        return NONE_LEN;

    for (size_t i = pos; i < len; i++) {
        for (size_t j = 0; j < s.len; j++) {
            if (str[i] == s.str[j])
                return i;
        }
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_of(const T* s, size_t pos) const {
    if (NULL == s)
        return NONE_LEN;

    size_t slen = Character<T, size_t>::strlen(s);
    return find_first_of(s, pos, slen);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_of(const T* s, size_t pos, size_t n) const {
    if (pos >= len || NULL == s || 0 == n)
        return NONE_LEN;

    for (size_t i = pos; i < len; i++) {
        for (size_t j = 0; j < n; j++) {
            if (str[i] == s[j])
                return i;
        }
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_of(T c, size_t pos) const {
    return find(c, pos);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_not_of(const BaseStr<T, size_t>& s, size_t pos) const {
    if (pos >= len)
        return NONE_LEN;

    for (size_t i = pos; i < len; i++) {
        atbool found = FALSE;
        for (size_t j = 0; j < s.len; j++) {
            if (str[i] == s.str[j]) {
                found = TRUE;
                break;
            }
        }
        if (!found)
            return i;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_not_of(const T* s, size_t pos) const {
    if (NULL == s)
        return NONE_LEN;

    size_t slen = Character<T, size_t>::strlen(s);
    return find_first_not_of(s, pos, slen);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_not_of(const T* s, size_t pos, size_t n) const {
    if (pos >= len || NULL == s)
        return NONE_LEN;

    for (size_t i = pos; i < len; i++) {
        atbool found = FALSE;
        for (size_t j = 0; j < n; j++) {
            if (str[i] == s[j]) {
                found = TRUE;
                break;
            }
        }
        if (!found)
            return i;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_first_not_of(T c, size_t pos) const {
    if (pos >= len)
        return NONE_LEN;

    for (size_t i = pos; i < len; i++) {
        if (str[i] != c)
            return i;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_of(const BaseStr<T, size_t>& s, size_t pos) const {
    if (0 == len || 0 == s.len)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - 1 : pos;

    for (size_t i = start; i != NONE_LEN; i--) {
        for (size_t j = 0; j < s.len; j++) {
            if (str[i] == s.str[j])
                return i;
        }
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_of(const T* s, size_t pos) const {
    if (NULL == s)
        return NONE_LEN;

    size_t slen = Character<T, size_t>::strlen(s);
    return find_last_of(s, pos, slen);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_of(const T* s, size_t pos, size_t n) const {
    if (0 == len || NULL == s || 0 == n)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - 1 : pos;

    for (size_t i = start; i != NONE_LEN; i--) {
        for (size_t j = 0; j < n; j++) {
            if (str[i] == s[j])
                return i;
        }
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_of(T c, size_t pos) const {
    return rfind(c, pos);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_not_of(const BaseStr<T, size_t>& s, size_t pos) const {
    if (0 == len)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - 1 : pos;

    for (size_t i = start; i != NONE_LEN; i--) {
        atbool found = FALSE;
        for (size_t j = 0; j < s.len; j++) {
            if (str[i] == s.str[j]) {
                found = TRUE;
                break;
            }
        }
        if (!found)
            return i;
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_not_of(const T* s, size_t pos) const {
    if (NULL == s)
        return NONE_LEN;

    size_t slen = Character<T, size_t>::strlen(s);
    return find_last_not_of(s, pos, slen);
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_not_of(const T* s, size_t pos, size_t n) const {
    if (0 == len || NULL == s)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - 1 : pos;

    for (size_t i = start; i != NONE_LEN; i--) {
        atbool found = FALSE;
        for (size_t j = 0; j < n; j++) {
            if (str[i] == s[j]) {
                found = TRUE;
                break;
            }
        }
        if (!found)
            return i;
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
size_t BaseStr<T, size_t>::find_last_not_of(T c, size_t pos) const {
    if (0 == len)
        return NONE_LEN;

    size_t start = (pos >= len) ? len - 1 : pos;

    for (size_t i = start; i != NONE_LEN; i--) {
        if (str[i] != c)
            return i;
        if (0 == i)
            break;
    }

    return NONE_LEN;
}

template <typename T, typename size_t>
const BaseStr<T, size_t> BaseStr<T, size_t>::substr(size_t pos, size_t n) const {
    return BaseStr<T, size_t>(*this, pos, n, pool);
}

template <typename T, typename size_t>
atbool BaseStr<T, size_t>::compare(const BaseStr<T, size_t>& s) const {
    if (len != s.len)
        return FALSE;

    for (size_t i = 0; i < len; i++) {
        if (str[i] != s.str[i])
            return FALSE;
    }

    return TRUE;
}

template <typename T, typename size_t>
atbool BaseStr<T, size_t>::compare(size_t pos, size_t n, const BaseStr<T, size_t>& s) const {
    return compare(pos, n, s, 0, NONE_LEN);
}

template <typename T, typename size_t>
atbool BaseStr<T, size_t>::compare(size_t pos, size_t n, const BaseStr<T, size_t>& s, size_t subpos, size_t subn) const {
    if (pos >= len)
        return FALSE;

    size_t thisLen = len - pos;
    if (n != NONE_LEN && n < thisLen)
        thisLen = n;

    size_t sLen = 0;
    if (subpos < s.len) {
        sLen = s.len - subpos;
        if (subn != NONE_LEN && subn < sLen)
            sLen = subn;
    }

    if (thisLen != sLen)
        return FALSE;

    for (size_t i = 0; i < thisLen; i++) {
        if (str[pos + i] != s.str[subpos + i])
            return FALSE;
    }

    return TRUE;
}

template <typename T, typename size_t>
atbool BaseStr<T, size_t>::compare(const T* s) const {
    if (NULL == s)
        return (0 == len);

    size_t slen = Character<T, size_t>::strlen(s);

    if (len != slen)
        return FALSE;

    for (size_t i = 0; i < len; i++) {
        if (str[i] != s[i])
            return FALSE;
    }

    return TRUE;
}

template <typename T, typename size_t>
atbool BaseStr<T, size_t>::compare(size_t pos, size_t n, const T* s) const {
    if (NULL == s || pos >= len)
        return FALSE;

    size_t thisLen = len - pos;
    if (n != NONE_LEN && n < thisLen)
        thisLen = n;

    size_t slen = Character<T, size_t>::strlen(s);

    if (thisLen != slen)
        return FALSE;

    for (size_t i = 0; i < thisLen; i++) {
        if (str[pos + i] != s[i])
            return FALSE;
    }

    return TRUE;
}

template <typename T, typename size_t>
atbool BaseStr<T, size_t>::compare(size_t pos, size_t n, const T* s, size_t subpos, size_t subn) const {
    if (NULL == s || pos >= len)
        return FALSE;

    size_t thisLen = len - pos;
    if (n != NONE_LEN && n < thisLen)
        thisLen = n;

    size_t sLen = (subpos < Character<T, size_t>::strlen(s)) ? subn : 0;

    if (thisLen != sLen)
        return FALSE;

    for (size_t i = 0; i < thisLen; i++) {
        if (str[pos + i] != s[subpos + i])
            return FALSE;
    }

    return TRUE;
}

template <typename T, typename size_t>
atint BaseStr<T, size_t>::stoi(const BaseStr<T, size_t>& s, size_t* pos, atint base) {
}

template <typename T, typename size_t>
atlong BaseStr<T, size_t>::stol(const BaseStr<T, size_t>& s, size_t* pos, atint base) {
}

template <typename T, typename size_t>
atulong BaseStr<T, size_t>::stoul(const BaseStr<T, size_t>& s, size_t* pos, atint base) {
}

template <typename T, typename size_t>
atfloat BaseStr<T, size_t>::stof(const BaseStr<T, size_t>& s, size_t* pos, atint base) {
}

template <typename T, typename size_t>
atdouble BaseStr<T, size_t>::stod(const BaseStr<T, size_t>& s, size_t* pos, atint base) {
}

template <typename T, typename size_t>
BaseStr<T, size_t> BaseStr<T, size_t>::to_string(atint val) {
}

template <typename T, typename size_t>
atbool operator==(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2) {
    return s1.compare(s2);
}

template <typename T, typename size_t>
atbool operator!=(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2) {
    return !s1.compare(s2);
}

template <typename T, typename size_t>
atbool operator<(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2) {
    size_t minLen = (s1.len < s2.len) ? s1.len : s2.len;

    for (size_t i = 0; i < minLen; i++) {
        if (s1.str[i] < s2.str[i])
            return TRUE;
        if (s1.str[i] > s2.str[i])
            return FALSE;
    }

    return (s1.len < s2.len) ? TRUE : FALSE;
}

template <typename T, typename size_t>
atbool operator<=(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2) {
    return (s1 == s2 || s1 < s2);
}

template <typename T, typename size_t>
atbool operator>(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2) {
    return !(s1 <= s2);
}

template <typename T, typename size_t>
atbool operator>=(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2) {
    return (s1 == s2 || s1 > s2);
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s1, const BaseStr<T, size_t>& s2) {
    BaseStr<T, size_t> result(s1);
    result.append(s2);
    return result;
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(BaseStr<T, size_t>&& s1, const BaseStr<T, size_t>& s2) {
    s1.append(s2);
    return static_cast<BaseStr<T, size_t>&&>(s1);
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s1, BaseStr<T, size_t>&& s2) {
    s2.insert(0, s1);
    return static_cast<BaseStr<T, size_t>&&>(s2);
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(BaseStr<T, size_t>&& s1, BaseStr<T, size_t>&& s2) {
    s1.append(s2);
    return static_cast<BaseStr<T, size_t>&&>(s1);
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(const T* s1, const BaseStr<T, size_t>& s2) {
    BaseStr<T, size_t> result(s1);
    result.append(s2);
    return result;
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(T c, const BaseStr<T, size_t>& s) {
    BaseStr<T, size_t> result(1, c);
    result.append(s);
    return result;
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s, const T* c) {
    BaseStr<T, size_t> result(s);
    result.append(c);
    return result;
}

template <typename T, typename size_t>
BaseStr<T, size_t> operator+(const BaseStr<T, size_t>& s, T c) {
    BaseStr<T, size_t> result(s);
    result.push_back(c);
    return result;
}

template <typename T, typename size_t>
atvoid swap(BaseStr<T, size_t>& s1, BaseStr<T, size_t>& s2) {
    s1.swap(s2);
}


} // end namespace atdb

#endif // AT_STR_H
