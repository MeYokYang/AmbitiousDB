#include "str_utils.h"

ulong SubStrSearch::brute_force_search(const Str& text, const Str& pattern, ulong start_pos)
{
    ulong text_len = text.length();
    ulong pattern_len = pattern.length();

    if (pattern_len == 0 || text_len < pattern_len || start_pos >= text_len)
        return ULONG_NONE; // Not found

    for (ulong i = start_pos; i <= text_len - pattern_len; ++i) {
        ulong j = 0;
        while (j < pattern_len && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == pattern_len) {
            return i; // Found at index i
        }
    }
    return ULONG_NONE; // Not found
}

Arr<ulong> SubStrSearch::compute_kmp_table(const Str& pattern)
{
    ulong pattern_len = pattern.length();
    Arr<ulong> kmp_table(pattern_len);
    kmp_table[0] = 0;

    ulong j = 0;
    for (ulong i = 1; i < pattern_len; ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = kmp_table[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        kmp_table[i] = j;
    }
    return kmp_table;
}

ulong SubStrSearch::kmp_search(const Str& text, const Str& pattern, ulong start_pos)
{
    ulong text_len = text.length();
    ulong pattern_len = pattern.length();

    if (pattern_len == 0 || text_len < pattern_len || start_pos >= text_len)
        return ULONG_NONE; // Not found

    Arr<ulong> kmp_table = compute_kmp_table(pattern);
    ulong j = 0;
    for (ulong i = start_pos; i < text_len; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = kmp_table[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == pattern_len) {
            return i - pattern_len + 1; // Found at index i - pattern_len + 1
        }
    }
    return ULONG_NONE; // Not found
}

Arr<ulong> SubStrSearch::compute_boyer_moore_bad_char_table(const Str& pattern)
{
    Arr<ulong> bad_char_table(256); // Assuming ASCII character set
    for (ulong i = 0; i < 256; ++i) {
        bad_char_table[i] = ULONG_NONE; // Initialize to not found
    }
    for (ulong i = 0; i < pattern.length(); ++i) {
        bad_char_table[(unsigned char)pattern[i]] = i; // Store last occurrence index
    }
    return bad_char_table;
}

Arr<ulong> SubStrSearch::compute_boyer_moore_good_suffix_table(const Str& pattern)
{
    ulong pattern_len = pattern.length();
    Arr<ulong> good_suffix_table(pattern_len);
    Arr<ulong> border_pos(pattern_len + 1);

    // Preprocessing for good suffix rule
    border_pos[pattern_len] = pattern_len + 1;
    ulong j = pattern_len + 1;
    for (long i = pattern_len; i > 0; --i) {
        while (j <= pattern_len && pattern[i - 1] != pattern[j - 1]) {
            if (good_suffix_table[j] == 0) {
                good_suffix_table[j] = j - i;
            }
            j = border_pos[j];
        }
        border_pos[i - 1] = --j;
    }

    // Fill the remaining entries in good suffix table
    for (ulong i = 0; i <= pattern_len; ++i) {
        if (good_suffix_table[i] == 0) {
            good_suffix_table[i] = j;
        }
        if (i == j) {
            j = border_pos[j];
        }
    }

    return good_suffix_table;
}

ulong SubStrSearch::boyer_moore_search(const Str& text, const Str& pattern, ulong start_pos)
{
    ulong text_len = text.length();
    ulong pattern_len = pattern.length();

    if (pattern_len == 0 || text_len < pattern_len || start_pos >= text_len)
        return ULONG_NONE; // Not found

    Arr<ulong> bad_char_table = compute_boyer_moore_bad_char_table(pattern);
    Arr<ulong> good_suffix_table = compute_boyer_moore_good_suffix_table(pattern);

    ulong s = start_pos; // s is the shift of the pattern with respect to text
    while (s <= text_len - pattern_len) {
        long j = pattern_len - 1;

        // Keep reducing j while characters of pattern and text are matching at this shift s
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }
        if (j < 0) {
            return s; // Found at index s
        } else {
            ulong bad_char_shift = j - bad_char_table[(unsigned char)text[s + j]];
            ulong good_suffix_shift = good_suffix_table[j + 1];
            s += MAX(bad_char_shift, good_suffix_shift);
        }
    }
    return ULONG_NONE; // Not found
}
