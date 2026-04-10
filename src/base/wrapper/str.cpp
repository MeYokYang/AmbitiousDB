#include "str.h"


Str::Str() : data(NULL), len(0) {}
Str::~Str()
{
    delete[] data;
    data = NULL;
    len = 0;
}

Str::Str(const Str& other) : data(NULL), len(0)
{
    len = other.len;
    if (len == 0)
        data = NULL;
    else {
        data = new char[len + 1];
        for (ulong i = 0; i < len; i++) {
            data[i] = other.data[i];
        }
        data[len] = '\0';
    }
}

Str& Str::operator=(const Str& other)
{
    if (this == &other)
        return *this;

    delete[] data;
    len = other.len;
    data = new char[len + 1];
    for (ulong i = 0; i < len; i++) {
        data[i] = other.data[i];
    }
    data[len] = '\0';

    return *this;
}

Str::Str(const char* str) : data(NULL), len(0)
{
    len = 0;

    if (str == NULL) 
        data = NULL;
    else {
        while (str[len] != '\0') { len++; }
        data = new char[len + 1];
        for (ulong i = 0; i < len; i++) {
            data[i] = str[i];
        }
        data[len] = '\0';
    }
}

bool operator==(const Str& lhs, const Str& rhs)
{
    if (lhs.len != rhs.len)
        return FALSE;
    for (ulong i = 0; i < lhs.len; i++) {
        if (lhs.data[i] != rhs.data[i])
            return FALSE;
    }
    return TRUE;
}

bool operator!=(const Str& lhs, const Str& rhs) { return (lhs == rhs) ? FALSE : TRUE; }

bool operator<(const Str& lhs, const Str& rhs)
{
    ulong minLen = (lhs.len < rhs.len) ? lhs.len : rhs.len;
    for (ulong i = 0; i < minLen; i++) {
        if (lhs.data[i] < rhs.data[i])
            return TRUE;
        else if (lhs.data[i] > rhs.data[i])
            return FALSE;
    }
    return (lhs.len < rhs.len) ? TRUE : FALSE;
}

bool operator>(const Str& lhs, const Str& rhs) { return (lhs < rhs) ? FALSE : TRUE; }

char& Str::operator[](ulong index) { return data[index]; }

const char& Str::operator[](ulong index) const { return data[index]; }
