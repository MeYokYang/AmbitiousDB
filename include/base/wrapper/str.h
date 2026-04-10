#ifndef STR_H
#define STR_H

#include "standard.h"
#include "object.h"


class Str : public Object
{
private:
    char* data;
    ulong len;
    static const ulong MAX_LEN = ULONG_MAX;

public:
    Str();
    ~Str();
    Str(const Str& other);
    Str& operator=(const Str& other);
    explicit Str(const char* str);

    ulong length() const { return len; }
    friend bool operator==(const Str& lhs, const Str& rhs);
    friend bool operator!=(const Str& lhs, const Str& rhs);
    friend bool operator<(const Str& lhs, const Str& rhs);
    friend bool operator>(const Str& lhs, const Str& rhs);
    char& operator[](ulong index);
    const char& operator[](ulong index) const;
};

#endif // STR_H

