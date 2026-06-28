#ifndef AT_STANDARD_H
#define AT_STANDARD_H

#include <limits>


// type definition
typedef void            atvoid;
typedef unsigned int    atbool;
typedef unsigned char   atbyte; 
typedef char            atchar; 
typedef signed short    atshort; 
typedef unsigned short  atushort;
typedef signed int      atint;
typedef unsigned int    atuint;  
typedef signed long     atlong; 
typedef unsigned long   atulong; 

#define TYPE_MAX(type)      (std::numeric_limits<type>::max() - 1)
#define TYPE_NONE(type)     (std::numeric_limits<type>::max())

#define NULL        nullptr
#define FALSE       0
#define TRUE        1
#define UNKNOWN     2

#endif // AT_STANDARD_H
