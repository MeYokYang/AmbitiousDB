#ifndef AMBI_STANDARD_H
#define AMBI_STANDARD_H

// null and boolean
#define NULL        nullptr
#define FALSE       0
#define TRUE        1
#define UNKNOWN     2

static const int ret_and[3][3] = {
    {FALSE, FALSE, FALSE},
    {FALSE, TRUE, UNKNOWN},
    {FALSE, UNKNOWN, UNKNOWN}
};

static const int ret_or[3][3] = {
    {FALSE, TRUE, UNKNOWN},
    {TRUE, TRUE, TRUE},
    {UNKNOWN, TRUE, UNKNOWN}
};

// comparison result
enum class CmpResult {
    CMP_UNKNOWN = 2,
    CMP_GREATER = 1,
    CMP_EQUAL   = 0,
    CMP_LESS    = -1
};

// type definition
#define boolean     byte
#define byte        unsigned char
#define char        char

#ifdef M32  // 32-bit machine
#define sshort      signed short
#define ushort      unsigned short
#define sint        signed int
#define uint        unsigned int
#define slong       signed long
#define ulong       unsigned long

#define USHORT_NONE     0xFFFF
#define USHORT_MAX      0xFFFE
#define UINT_NONE       0xFFFFFFFF
#define UINT_MAX        0xFFFFFFFE
#define ULONG_NONE      0xFFFFFFFFFFFFFFFF
#define ULONG_MAX       0xFFFFFFFFFFFFFFFE
#elif M64   // 64-bit machine
#define sshort      signed short
#define ushort      unsigned short
#define sint        signed int
#define uint        unsigned int
#define slong       signed long
#define ulong       unsigned long

#define USHORT_NONE     0xFFFF
#define USHORT_MAX      0xFFFE
#define UINT_NONE       0xFFFFFFFF
#define UINT_MAX        0xFFFFFFFE
#define ULONG_NONE      0xFFFFFFFFFFFFFFFF
#define ULONG_MAX       0xFFFFFFFFFFFFFFFE
#else // default
#define sshort      signed short
#define ushort      unsigned short
#define sint        signed int
#define uint        unsigned int
#define slong       signed long
#define ulong       unsigned long

#define USHORT_NONE     0xFFFF
#define USHORT_MAX      0xFFFE
#define UINT_NONE       0xFFFFFFFF
#define UINT_MAX        0xFFFFFFFE
#define ULONG_NONE      0xFFFFFFFFFFFFFFFF
#define ULONG_MAX       0xFFFFFFFFFFFFFFFE
#endif

#define get_type_max(type) ({\
    switch (type) {\
    case ushort:\
        return USHORT_MAX;\
    case uint:\
        return UINT_MAX;\
    case ulong:\
        return ULONG_MAX;\
    default:\
        return 0;\
    }\
})

#define get_type_none(type) ({\
    switch (type) {\
    case ushort:\
        return USHORT_NONE;\
    case uint:\
        return UINT_NONE;\
    case ulong:\
        return ULONG_NONE;\
    default:\
        return 0;\
    }\
})

#endif // AMBI_STANDARD_H
