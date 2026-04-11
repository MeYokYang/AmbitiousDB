#ifndef STR_UTILS_H
#define STR_UTILS_H

#include "str.h"
#include "arr.h"


class SubStrSearch
{
private:
    static Arr<ulong> compute_kmp_table(const Str& pattern);
    static Arr<ulong> compute_boyer_moore_bad_char_table(const Str& pattern);
    static Arr<ulong> compute_boyer_moore_good_suffix_table(const Str& pattern);

public:
    SubStrSearch() = default;
    ~SubStrSearch() = default;

    static ulong brute_force_search(const Str& text, const Str& pattern, ulong start_pos = 0);
    static ulong kmp_search(const Str& text, const Str& pattern, ulong start_pos = 0);
    static ulong boyer_moore_search(const Str& text, const Str& pattern, ulong start_pos = 0);

};

#endif // STR_UTILS_H
