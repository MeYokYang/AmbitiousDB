#include "ambi/mem/at_pool.h"

namespace atdb {

    
atbool initMem() {

    try {
        MemPool<> systemPool    = MemPool<>(PoolType::POOL_SYSTEM, 64);
        MemPool<> constPool     = MemPool<>(PoolType::POOL_CONST, 64);
    } catch (Code c) {
        return FALSE;
    }

    return TRUE;
}

INLINE
MemPool<>& getSystemPool() { return systemPool; }

INLINE
MemPool<>& getConstPool() { return constPool; }


} // end namespace atdb
