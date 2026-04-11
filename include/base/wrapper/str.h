#ifndef STR_H
#define STR_H

#include "object.h"
#include "standard.h"
#include "tag.h"


class Str : public Object, public Comparable, public RandomAccessible<char, ulong>
{
private:
    static const ulong  MAX_LEN = ULONG_MAX;
    char*               data;
    ulong               len;

public:
    Str();
    ~Str();
    Str(const Str& other);
    Str& operator=(const Str& other);
    explicit Str(const char* str);

    bool operator==(const Comparable& other) const override;
    bool operator<(const Comparable& other) const override;

    char& operator[](ulong index) override;
    const char& operator[](ulong index) const override;

    ulong length() const { return len; }

};

#endif // STR_H

