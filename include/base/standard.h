#ifndef STANDARD_H
#define STANDARD_H

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
#define CMP_GREATER 1
#define CMP_EQUAL   0
#define CMP_LESS    -1

// type definition
#define bool        bool
#define byte        unsigned char
#define char        char

#ifdef M32  // 32-bit machine
#define sint        signed int
#define uint        unsigned int
#define slong       signed long
#define ulong       unsigned long
#define sshort      signed short
#define ushort      unsigned short
#define ULONG_NONE      0xFFFFFFFFFFFFFFFF
#define ULONG_MAX       0xFFFFFFFFFFFFFFFE
#elif M64   // 64-bit machine
#define sint        signed int
#define uint        unsigned int
#define slong       signed long
#define ulong       unsigned long
#define sshort      signed short
#define ushort      unsigned short
#define ULONG_NONE      0xFFFFFFFFFFFFFFFF
#define ULONG_MAX       0xFFFFFFFFFFFFFFFE
#else // default
#define sint        signed int
#define uint        unsigned int
#define slong       signed long
#define ulong       unsigned long
#define sshort      signed short
#define ushort      unsigned short
#define ULONG_NONE      0xFFFFFFFFFFFFFFFF
#define ULONG_MAX       0xFFFFFFFFFFFFFFFE
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif // STANDARD_H
