#ifndef TAG_H
#define TAG_H

#include "standard.h"
#include "iterator.h"

class Cloneable
{
public:
    virtual ~Cloneable() = default;

    virtual Cloneable* clone() const = 0;

};

class Comparable
{
public:
    virtual ~Comparable() = default;

    virtual bool operator==(const Comparable& other) const = 0;
    bool operator!=(const Comparable& other) const { return (*this == other) ? FALSE : TRUE; };
    virtual bool operator<(const Comparable& other) const = 0;
    bool operator>(const Comparable& other) const { return (*this <= other) ? FALSE : TRUE; };
    bool operator<=(const Comparable& other) const{ return (*this < other) || (*this == other); };
    bool operator>=(const Comparable& other) const { return (*this > other) || (*this == other); };

};

template <typename T, typename U = ulong>
class RandomAccessible
{
public:
    virtual ~RandomAccessible() = default;

    virtual T& operator[](U index) = 0;
    virtual const T& operator[](U index) const = 0;

};

template <typename T>
class Iterable
{
public:
    virtual ~Iterable() = default;

    virtual Iterator<T>& iterator() = 0;
    //virtual void forEach(Consumer<T> consumer) = 0;
    //Spliterator<T> spliterator() = 0;

};

#endif // TAG_H
