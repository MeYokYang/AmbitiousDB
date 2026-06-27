#ifndef AMBI_ABSTR_COLLECTION_H
#define AMBI_ABSTR_COLLECTION_H

#include "ambi/standard.h"
#include "ambi/util/collection.h"
#include "ambi/util/iterator.h"

namespace ambi {

template <typename T>
class AbstrCollection : public Collection<T>
{
private:

public:
    virtual ~AbstrCollection() = default;

    virtual boolean isEmpty() const override { return this->size() == 0 ? TRUE : FALSE; }
    virtual boolean contains(const T& d) const override;

};

template <typename T>
boolean AbstrCollection<T>::contains(const T& d) const { 
    Iterator<T> it = this->iterator();
}



    
} // namespace ambi


#endif // AMBI_ABSTR_COLLECTION_H
