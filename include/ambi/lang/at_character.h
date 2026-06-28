#ifndef AT_CHARACTER_H
#define AT_CHARACTER_H

#include <cstring>

namespace atdb {


template <typename T, typename size_t>
class Character {
public:
    static size_t strlen(const T* p) { return strlen(p); };

};


} // end namespace atdb

#endif // AT_ATCHAR_H
