#include "str.h"
#include "format.h"


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
    if (len == 0) {
        data = NULL;
    } else {
        data = new char[len + 1];
        for (ulong i = 0; i < len; i++) {
            data[i] = other.data[i];
        }
        data[len] = '\0';
    }
    return *this;
}

Str::Str(const char* str) : data(NULL), len(0)
{
    if (str == NULL) {
        data = NULL;
        len = 0;
    } else {
        len = 0;
        while (str[len] != '\0') {
            len++;
        }
        data = new char[len + 1];
        for (ulong i = 0; i < len; i++) {
            data[i] = str[i];
        }
        data[len] = '\0';
    }
}

bool Str::operator==(const Comparable& other) const
{
    const Str* other_str = dynamic_cast<const Str*>(&other);
    if (!other_str) {
        return FALSE; // Not comparable
    }
    if (len != other_str->len) {
        return FALSE;
    }
    for (ulong i = 0; i < len; i++) {
        if (data[i] != other_str->data[i]) {
            return FALSE;
        }
    }
    return TRUE;
}

bool Str::operator<(const Comparable& other) const
{
    const Str* other_str = dynamic_cast<const Str*>(&other);
    if (!other_str) {
        return FALSE; // Not comparable
    }
    ulong min_len = (len < other_str->len) ? len : other_str->len;
    for (ulong i = 0; i < min_len; i++) {
        if (data[i] < other_str->data[i]) {
            return TRUE;
        } else if (data[i] > other_str->data[i]) {
            return FALSE;
        }
    }
    return len < other_str->len ? TRUE : FALSE;
}

char& Str::operator[](ulong index)
{
    if (index >= len) {
        // TODO
    }
    return data[index];
}

const char& Str::operator[](ulong index) const
{
    if (index >= len) {
        // TODO
    }
    return data[index];
}
