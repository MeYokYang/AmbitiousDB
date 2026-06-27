#ifndef AMBI_ITERABLE_H
#define AMBI_ITERABLE_H

namespace ambi {

template <typename T>
class Iterable
{
public:
    virtual ~Iterable() = default;

    virtual Iterator<T>& iterator() = 0;
    //virtual void forEach(Consumer<T> consumer) = 0;
    //Spliterator<T> spliterator() = 0;

};

} // namespace ambi

#endif // AMBI_ITERABLE_H
