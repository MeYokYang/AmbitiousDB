#ifndef AT_STANDARD_H
#define AT_STANDARD_H

#include <limits>


// type definition
#define atvoid      void
#define atbool      uint
#define atbyte      unsigned char
#define atchar      char
#define sshort      signed short
#define ushort      unsigned short
#define sint        signed int
#define uint        unsigned int
#define slong       signed long
#define ulong       unsigned long

#define ushort_NONE     0xFFFF
#define ushort_MAX      0xFFFE
#define uint_NONE       0xFFFFFFFF
#define uint_MAX        0xFFFFFFFE
#define ulong_NONE      0xFFFFFFFFFFFFFFFF
#define ulong_MAX       0xFFFFFFFFFFFFFFFE

#define TYPE_MAX(type)      (std::numeric_limits<type>::max() - 1)
#define TYPE_NONE(type)     (std::numeric_limits<type>::max())

#define NULL        nullptr
#define FALSE       0
#define TRUE        1
#define UNKNOWN     2

#endif // AT_STANDARD_H
