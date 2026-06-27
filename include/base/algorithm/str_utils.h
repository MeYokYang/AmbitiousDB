#ifndef AMBI_STR_UTILS_H
#define AMBI_STR_UTILS_H

#include "type/common/vec.h"
#include "type/common/str.h"

namespace ambi {

class SubStrSearch
{
private:
    static Vec<ulong> compute_kmp_table(const Str& pattern);
    static Vec<ulong> compute_boyer_moore_bad_char_table(const Str& pattern);
    static Vec<ulong> compute_boyer_moore_good_suffix_table(const Str& pattern);

public:
    SubStrSearch() = default;
    ~SubStrSearch() = default;

    static ulong brute_force_search(const Str& text, const Str& pattern, ulong start_pos = 0);
    static ulong kmp_search(const Str& text, const Str& pattern, ulong start_pos = 0);
    static ulong boyer_moore_search(const Str& text, const Str& pattern, ulong start_pos = 0);

};

} // namespace ambi

#endif // STR_UTILS_H
