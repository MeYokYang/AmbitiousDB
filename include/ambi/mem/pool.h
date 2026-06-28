#ifndef AT_POOL_H
#define AT_POOL_H

#include "ambi/base/code.h"
#include "ambi/base/format.h"
#include "ambi/base/type.h"
#include <new>

namespace atdb {

enum class PoolType {
    POOL_SYSTEM, // 系统内存池
    POOL_CONST,  // 常量内存池
    POOL_SHARE,  // 共享内存池
    POOL_NORMAL, // 普通内存池
};

template <typename size_t = ulong> class MemPool {
private:
    PoolType type;
    MemPool *parent;
    size_t size;
    size_t used;
    atbyte *ptr;

    atbool poolInit();

public:
    MemPool(PoolType t, size_t s, MemPool *p = NULL);
    ~MemPool();
    // MemPool(const MemPool&) = delete;
    // MemPool& operator=(const MemPool&) = delete;

    atbyte *alloc(size_t s);
    atbool free(atbyte *p);
    atbool free(MemPool<> &subPool);
};

template <typename size_t>
MemPool<size_t>::MemPool(PoolType t, size_t s, MemPool *p) {
    type = t;
    size = s;
    used = 0;

    if (NULL == p) {
        // 从OS上分配
        parent = NULL;
        ptr = new (std::nothrow) atbyte[s];
        THROW_IF_NULL(ptr, Code::OUT_OF_MEMORY);
    } else {
        // 从parent上分配

        // parent分配失败，从共享池上分配
    }

    THROW_IF_NOT_TRUE(poolInit(), Code::MEMPOOL_INIT_ERR);
}

template <typename size_t> MemPool<size_t>::~MemPool() {
    if (NULL == parent) {
        // 从OS上释放
        delete[] ptr;

    } else {
        // 从父池上释放
        parent->free(*this);
    }
}

template <typename size_t> atbyte *MemPool<size_t>::alloc(size_t s) {

    try {
        // TODO
    } catch (Code c) {
        throw Code::OUT_OF_MEMORY;
    }

    return NULL;
}

template <typename size_t> atbool MemPool<size_t>::free(atbyte *p) {
    // TODO

    return TRUE;
}

template <typename size_t> atbool MemPool<size_t>::free(MemPool<> &subPool) {
    // TODO

    return TRUE;
}

template <typename size_t> atbool MemPool<size_t>::poolInit() {
    // TODO 

    return TRUE;
}

extern MemPool<> systemPool;
extern MemPool<> constPool;

atbool initMem();

INLINE
MemPool<> &getSystemPool();

INLINE
MemPool<> &getConstPool();

} // end namespace atdb

#endif // AT_POOL_H
