#include <cstdint>
#include <typeinfo>
#include "object.h"


inline const ulong Object::hashCode() const { return reinterpret_cast<ulong>(this); }
inline const char* Object::toString() const { return typeid(*this).name(); };
inline bool Object::equals(const Object& other) const { return this->hashCode() == other.hashCode() ? TRUE : FALSE; };
