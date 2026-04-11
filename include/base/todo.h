#ifndef TODO_H
#define TODO_H

#include "standard.h"
#include "arr.h"
#include "str.h"

bool burrow_wheeler_transform(const char* input, char*& output, ulong& index);
bool inverse_burrow_wheeler_transform(const char* input, char*& output, ulong index);

bool lossy_counting(const Arr<Str>& items, ulong support_threshold, Arr<Str>& frequent_items);

#endif // TODO_H
