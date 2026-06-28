#ifndef AT_STR_H
#define AT_STR_H

#include "ambi/mem/at_pool.h"
#include "ambi/lang/at_character.h"

namespace atdb {


#define Str                 BaseStr<atchar, atuint>

template <typename T = atchar, typename size_t = atuint>
class BaseStr {
private:
    MemPool<>           pool;
    static const size_t MAX_LEN = TYPE_MAX(size_t);
    T*                  str;
    size_t              len;
    size_t              cap;

public:
    // ctor
    BaseStr() : pool(getConstPool()), str(NULL), len(0), cap(0) {};
    BaseStr(const BaseStr<T, size_t>& other);
    explicit BaseStr(const T* s);
    BaseStr(size_t s, T c);
    ~BaseStr();
    BaseStr(const BaseStr<T, size_t>&& other);
    BaseStr operator=(const BaseStr<T, size_t>& other);
    BaseStr operator=(const BaseStr<T, size_t>&& other);
    // TODO assign

    // capacity
    size_t size() const { return len; }
    atbool empty() const { return 0 == len; }
    size_t capacity() const { return cap; }
    size_t reserve() const { return cap - len; }
    atbool shrink_to_fit();
    atvoid clear();

    // modify
    BaseStr<T, size_t>& operator+=(const BaseStr<T, size_t> other);
    BaseStr<T, size_t>& append(const BaseStr<T, size_t> other) { return this + other; }
    BaseStr<T, size_t>& push_back();
    BaseStr<T, size_t>& insert(T c, size_t pos);
    BaseStr<T, size_t>& erase();
    BaseStr<T, size_t>& replace();
    BaseStr<T, size_t>& swap();
    BaseStr<T, size_t>& pop_back();

    // search and compare
    size_t find(T c, size_t start = 0) const;
    size_t rfind(T c, size_t start) const;
    size_t find_first_of(T c) const;
    size_t find_first_not_of(T c) const;
    size_t find_last_of(T c) const;
    size_t find_last_not_of(T c) const;
    size_t substr() const;
    atbool compare() const;

    // convert
    atint stoi() const;
    atlong stol() const;
    // TODO stod
    T* to_string() const;
};

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(const BaseStr<T, size_t>& other) {
    MemPool<> constPool = getConstPool();

    at_assert(other.pool == constPool);

    if (0 == other.len) {
        BaseStr();
    } else {
        at_assert(NULL != other.str);

        pool    = constPool;
        len     = other.len;
        cap     = other.len;
        str     = NULL;

        try {
            str = constPool.alloc(sizeof(T) * other.len);
            at_memcpy(str, sizeof(T) * len, other.str, sizeof(T) * other.len);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(const T* s) {
    MemPool<> constPool = getConstPool();

    if (NULL == s) {
        BaseStr();
    } else {
        pool    = constPool;
        len     = Character<T, size_t>::strlen(s);
        cap     = len;

        try {
            str = constPool.alloc(sizeof(T) * len);
            at_memcpy(str, sizeof(T) * len, s, sizeof(T) * len);
        } catch (Code c) {
            throw c;
        }
    }
}

template <typename T, typename size_t>
BaseStr<T, size_t>::BaseStr(size_t s, T c) {
    MemPool<>   constPool = getConstPool();

    if (0 == s) {
        BaseStr();
    } else {
        pool    = constPool;
        len     = s;
        cap     = s;

        try {
            str = constPool.alloc(sizeof(T) * len);

            for (size_t i = 0; i < len; i++)
                str[i] = c;
        } catch (Code c) {
            throw c;
        }
    }
}

// TODO



} // end namespace atdb

#endif // AT_STR_H
