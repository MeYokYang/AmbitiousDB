#ifndef AMBI_STR_H
#define AMBI_STR_H

#include "standard.h"

namespace ambi{


typedef     BaseStr<char>   Str;

#define     _str_size_t                     ulong
#define     _str_max_len                    get_type_max(_str_size_t)
#define     _str_size_none                  get_type_none(_str_size_t)
//#define     _str_storage_type_threshold     64

template <typename T>
class BaseStr
{
private:
    //enum class STORAGE_TYPE { STACK, HEAP };
    _str_size_t             capacity;
    _str_size_t             len;
    T*                      data;
    //STORAGE_TYPE            type;

public:
    explicit BaseStr(const T* s = NULL);
    BaseStr(_str_size_t l, const T c);
    BaseStr(const BaseStr<T>& other);
    BaseStr<T>& operator=(const BaseStr<T>& other);
    ~BaseStr() { delete[] data; };

    boolean assign(const T* s);
    boolean assign(_str_size_t l, const T& c);
    boolean assign(const BaseStr<T>& other);
    boolean swap(BaseStr<T>& other);

    T& operator[](_str_size_t index) { return data[index]; }
    const T& operator[](_str_size_t index) const { return data[index]; }
    T& at(_str_size_t index);
    const T& at(_str_size_t index) const;
    T& front() { return data[0]; }
    const T& front() const { return data[0]; }
    T& back() { return data[len - 2]; }
    const T& back() const { return data[len - 2]; }
    T* data() { return data; }
    const T* data() const { return data; }

    // iter
    // TODO

    boolean empty() const { return len == 0 ? TRUE : FALSE; }
    _str_size_t size() const { return len; }
    _str_size_t length() const { return len; }
    _str_size_t max_size() const { return _str_max_len; }
    _str_size_t capacity() const { return capacity; }
    boolean reserve(_str_size_t l);
    boolean shrink_to_fit();

    BaseStr<T>& clear();
    BaseStr<T>& insert(_str_size_t pos, const T* s);
    BaseStr<T>& insert(_str_size_t pos, _str_size_t l, const T c);
    BaseStr<T>& insert(_str_size_t pos, const BaseStr<T>& other);
    BaseStr<T>& erase(_str_size_t pos, _str_size_t l = _str_size_none);
    BaseStr<T>& push_back(const T& c);
    BaseStr<T>& pop_back();
    BaseStr<T>& append(const BaseStr<T>& other);
    BaseStr<T>& append(const T* s);
    BaseStr<T>& append(_str_size_t l, const T c);
    BaseStr<T>& operator+=(const BaseStr<T>& other);
    BaseStr<T>& operator+=(const T* s);
    BaseStr<T>& operator+=(const T c);
    BaseStr<T>& replace(_str_size_t pos, _str_size_t l, const T* s);
    BaseStr<T>& replace(_str_size_t pos, _str_size_t l, const BaseStr<T>& other);
    BaseStr<T>& resize(_str_size_t l);
    BaseStr<T>& resize(_str_size_t l, const T& c);
    BaseStr<T>& substr(_str_size_t pos, _str_size_t l = _str_size_none);
    //copy()

    _str_size_t find(const T* s, _str_size_t pos = 0) const;
    _str_size_t find(const BaseStr<T>& other, _str_size_t pos = 0) const;
    _str_size_t find(const T& c, _str_size_t pos = 0) const;
    _str_size_t rfind(const T* s, _str_size_t pos = 0) const;
    _str_size_t rfind(const BaseStr<T>& other, _str_size_t pos = 0) const;
    _str_size_t rfind(const T& c, _str_size_t pos = 0) const;
    _str_size_t find_first_of(const T* s, _str_size_t pos = 0) const;
    _str_size_t find_first_of(const BaseStr<T>& other, _str_size_t pos = 0) const;
    _str_size_t find_first_of(const T& c, _str_size_t pos = 0) const;
    _str_size_t find_last_of(const T* s, _str_size_t pos = 0) const;
    _str_size_t find_last_of(const BaseStr<T>& other, _str_size_t pos = 0) const;
    _str_size_t find_last_of(const T& c, _str_size_t pos = 0) const;
    _str_size_t find_first_not_of(const T* s, _str_size_t pos = 0) const;
    _str_size_t find_first_not_of(const BaseStr<T>& other, _str_size_t pos = 0) const;
    _str_size_t find_first_not_of(const T& c, _str_size_t pos = 0) const;
    _str_size_t find_last_not_of(const T* s, _str_size_t pos = 0) const;
    _str_size_t find_last_not_of(const BaseStr<T>& other, _str_size_t pos = 0) const;
    _str_size_t find_last_not_of(const T& c, _str_size_t pos = 0) const;

    CmpResult compare(const BaseStr<T>& other) const;
    CmpResult compare(const T* s) const;
    CmpResult operator==(const BaseStr<T>& other) const { return compare(other) == CmpResult::CMP_EQUAL ? TRUE : FALSE; }
    CmpResult operator==(const T* s) const { return compare(s) == CmpResult::CMP_EQUAL ? TRUE : FALSE; }
    CmpResult operator!=(const BaseStr<T>& other) const { return *this == other ? FALSE : TRUE; }
    CmpResult operator!=(const T* s) const { return *this == s ? FALSE : TRUE; }
    CmpResult operator<(const BaseStr<T>& other) const { return compare(other) == CmpResult::CMP_LESS ? TRUE : FALSE; }
    CmpResult operator<(const T* s) const { return compare(s) == CmpResult::CMP_LESS ? TRUE : FALSE; }
    CmpResult operator>(const BaseStr<T>& other) const { return other < *this; }
    CmpResult operator>(const T* s) const { return s < *this; }
    CmpResult operator<=(const BaseStr<T>& other) const { return other > *this ? FALSE : TRUE; }
    CmpResult operator<=(const T* s) const { return s > *this ? FALSE : TRUE; }
    CmpResult operator>=(const BaseStr<T>& other) const { return other < *this ? FALSE : TRUE; }
    CmpResult operator>=(const T* s) const { return s < *this ? FALSE : TRUE; }

    //int stoi() const;
    //double stod() const;

};

template <typename T>
BaseStr<T>::BaseStr(const T* s) {
    if (s == NULL) {
        capacity = 0;
        len = 0;
        data = NULL;
    } else {
        for (len = 0; s[len] != '\0'; len++);
        data = new T[len + 1];
        for (_str_size_t i = 0; i < len; i++)
            data[i] = s[i];
        data[len] = '\0';
    }
}

template <typename T>
BaseStr<T>::BaseStr(_str_size_t l, const T c) {
    len = l;
    data = new T[len + 1];
    for (_str_size_t i = 0; i < len; i++)
        data[i] = c;
    data[len] = '\0';
}

template <typename T>
BaseStr<T>::BaseStr(const BaseStr<T>& other) {
    len = other.len;
    data = new T[len + 1];
    for (_str_size_t i = 0; i < len; i++)
        data[i] = other.data[i];
    data[len] = '\0';
}

template <typename T>
BaseStr<T>& BaseStr<T>::operator=(const BaseStr<T>& other) {
    if (this == &other)
        return *this;

    delete[] data;
    len = other.len;
    data = new T[len + 1];
    for (_str_size_t i = 0; i < len; i++)
        data[i] = other.data[i];
    data[len] = '\0';
    return *this;
}

template <typename T>
boolean BaseStr<T>::assign(const T *s)
{
    
}

template <typename T>
inline boolean BaseStr<T>::assign(_str_size_t l, const T &c)
{
    return false;
}

template <typename T>
inline boolean BaseStr<T>::assign(const BaseStr<T> &other)
{
    return false;
}

template <typename T>
inline boolean BaseStr<T>::swap(BaseStr<T> &other)
{
    return false;
}

template <typename T>
inline T &BaseStr<T>::at(_str_size_t index)
{
    // TODO: insert return statement here
}

template <typename T>
inline const T &BaseStr<T>::at(_str_size_t index) const
{
    // TODO: insert return statement here
}

template <typename T>
inline boolean BaseStr<T>::reserve(_str_size_t l)
{
    return boolean();
}

template <typename T>
inline boolean BaseStr<T>::shrink_to_fit()
{
    return boolean();
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::clear()
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::insert(_str_size_t pos, const T *s)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::insert(_str_size_t pos, _str_size_t l, const T c)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::insert(_str_size_t pos, const BaseStr<T> &other)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::erase(_str_size_t pos, _str_size_t l)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::push_back(const T &c)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::pop_back()
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::append(const BaseStr<T> &other)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::append(const T *s)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::append(_str_size_t l, const T c)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::operator+=(const BaseStr<T> &other)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::operator+=(const T *s)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::operator+=(const T c)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::replace(_str_size_t pos, _str_size_t l, const T *s)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::replace(_str_size_t pos, _str_size_t l, const BaseStr<T> &other)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::resize(_str_size_t l)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::resize(_str_size_t l, const T &c)
{
    // TODO: insert return statement here
}

template <typename T>
inline BaseStr<T> &BaseStr<T>::substr(_str_size_t pos, _str_size_t l)
{
    // TODO: insert return statement here
}

template <typename T>
inline _str_size_t BaseStr<T>::find(const T *s, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find(const BaseStr<T> &other, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find(const T &c, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::rfind(const T *s, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::rfind(const BaseStr<T> &other, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::rfind(const T &c, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_first_of(const T *s, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_first_of(const BaseStr<T> &other, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_first_of(const T &c, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_last_of(const T *s, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_last_of(const BaseStr<T> &other, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_last_of(const T &c, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_first_not_of(const T *s, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_first_not_of(const BaseStr<T> &other, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_first_not_of(const T &c, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_last_not_of(const T *s, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_last_not_of(const BaseStr<T> &other, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline _str_size_t BaseStr<T>::find_last_not_of(const T &c, _str_size_t pos) const
{
    return _str_size_t();
}

template <typename T>
inline CmpResult BaseStr<T>::compare(const BaseStr<T> &other) const
{
    return CmpResult();
}

template <typename T>
inline CmpResult BaseStr<T>::compare(const T *s) const
{
    return CmpResult();
}

} // namespace ambi

#endif // AMBI_STR_H
