#include "ambi/mem/at_pool.h"

namespace atdb {

static char _systemPoolMem[sizeof(MemPool<>)];
static char _constPoolMem[sizeof(MemPool<>)];
static char _stringPoolMem[sizeof(MemPool<>)];

MemPool<>& systemPool  = *(MemPool<>*)_systemPoolMem;
MemPool<>& constPool   = *(MemPool<>*)_constPoolMem;
MemPool<>& stringPool  = *(MemPool<>*)_stringPoolMem;

atbool initMem() {
    try {
        ::new (_systemPoolMem) MemPool<>(PoolType::POOL_SYSTEM, 64);
        ::new (_constPoolMem) MemPool<>(PoolType::POOL_CONST, 64);
        ::new (_stringPoolMem) MemPool<>(PoolType::POOL_STRING, 64);
    } catch (Code c) {
        return FALSE;
    }
    return TRUE;
}

} // end namespace atdb
