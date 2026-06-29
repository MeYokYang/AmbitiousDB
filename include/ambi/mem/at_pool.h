#ifndef AT_POOL_H
#define AT_POOL_H

#include "ambi/base/at_code.h"
#include "ambi/base/at_format.h"
#include "ambi/base/at_type.h"
#include <new>

namespace atdb {

enum class PoolType {
    POOL_SYSTEM, // 系统内存池
    POOL_CONST,  // 常量内存池
    POOL_SHARE,  // 共享内存池
    POOL_NORMAL, // 普通内存池
    POOL_STRING, // 字符串内存池
};

template <typename size_t = atulong> 
class MemPool {
private:
    static const atuint MIN_BLOCK_ORDER = 6;
    static const size_t MIN_BLOCK = (size_t)1 << MIN_BLOCK_ORDER;
    static const atuint MAX_BITS = sizeof(size_t) * 8;

    struct BlockHead {
        size_t   magic;
        size_t   blkSize;
        MemPool* owner;
    };

    struct FreeNode {
        FreeNode* next;
        FreeNode* prev;
    };

    PoolType    type;
    MemPool*    parent;
    size_t      poolSize;
    size_t      used;
    atbyte*     ptr;
    atuint      maxOrder;
    FreeNode*   freeLists[MAX_BITS];

    atbool poolInit();
    atuint orderFromSize(size_t blkSize) const;
    size_t sizeFromOrder(atuint order) const;
    void addToFreeList(atbyte* addr, size_t blkSize);
    void removeFromFreeList(FreeNode* node, atuint order);
    atbyte* splitBlock(atbyte* addr, size_t blkSize, size_t targetSize);

public:
    MemPool(PoolType t, size_t s, MemPool *p = NULL);
    ~MemPool();

    atbyte* alloc(size_t s);
    atbool free(atbyte *p);
    atbool free(MemPool<> &subPool);
};

template <typename size_t>
atuint MemPool<size_t>::orderFromSize(size_t blkSize) const {
    atuint order = 0;
    size_t sz = MIN_BLOCK;
    while (sz < blkSize) {
        sz <<= 1;
        order++;
    }
    return order;
}

template <typename size_t>
size_t MemPool<size_t>::sizeFromOrder(atuint order) const {
    return (size_t)MIN_BLOCK << order;
}

template <typename size_t>
void MemPool<size_t>::addToFreeList(atbyte* addr, size_t blkSize) {
    BlockHead* hdr = (BlockHead*)addr;
    hdr->magic   = (size_t)0x46524545;
    hdr->blkSize = blkSize;
    hdr->owner   = this;

    atuint order = orderFromSize(blkSize);
    FreeNode* node = (FreeNode*)(addr + sizeof(BlockHead));
    node->next = freeLists[order];
    node->prev = NULL;

    if (freeLists[order] != NULL)
        freeLists[order]->prev = node;

    freeLists[order] = node;
}

template <typename size_t>
void MemPool<size_t>::removeFromFreeList(FreeNode* node, atuint order) {
    if (node->prev != NULL)
        node->prev->next = node->next;
    else
        freeLists[order] = node->next;

    if (node->next != NULL)
        node->next->prev = node->prev;
}

template <typename size_t>
atbyte* MemPool<size_t>::splitBlock(atbyte* addr, size_t blkSize, size_t targetSize) {
    while (blkSize > targetSize) {
        blkSize >>= 1;
        atbyte* buddy = addr + blkSize;
        addToFreeList(buddy, blkSize);
    }
    return addr;
}

template <typename size_t>
MemPool<size_t>::MemPool(PoolType t, size_t s, MemPool *p) {
    type     = t;
    poolSize = s;
    used     = 0;

    if (NULL == p) {
        parent = NULL;
        ptr = new (std::nothrow) atbyte[s];
        THROW_IF_NULL(ptr, Code::OUT_OF_MEMORY);
    } else {
        parent = p;
        ptr = p->alloc(s);
        THROW_IF_NULL(ptr, Code::OUT_OF_MEMORY);
    }

    THROW_IF_NOT_TRUE(poolInit(), Code::MEMPOOL_INIT_ERR);
}

template <typename size_t> MemPool<size_t>::~MemPool() {
    if (NULL == parent) {
        delete[] ptr;
    } else {
        parent->free(*this);
    }
}

template <typename size_t> atbool MemPool<size_t>::poolInit() {
    for (atuint i = 0; i < MAX_BITS; i++)
        freeLists[i] = NULL;

    size_t maxBlk = MIN_BLOCK;
    maxOrder = 0;
    while ((maxBlk << 1) <= poolSize) {
        maxBlk <<= 1;
        maxOrder++;
    }

    atbyte* addr = ptr;
    size_t remaining = poolSize;

    while (remaining >= MIN_BLOCK) {
        size_t blockSize = MIN_BLOCK;
        while ((blockSize << 1) <= remaining)
            blockSize <<= 1;

        addToFreeList(addr, blockSize);
        addr += blockSize;
        remaining -= blockSize;
    }

    return TRUE;
}

template <typename size_t> atbyte* MemPool<size_t>::alloc(size_t s) {
    if (0 == s)
        return NULL;

    size_t needed = sizeof(BlockHead) + s;
    size_t blockSize = MIN_BLOCK;
    while (blockSize < needed)
        blockSize <<= 1;

    atuint order = orderFromSize(blockSize);
    atuint foundOrder = order;

    while (foundOrder <= maxOrder && NULL == freeLists[foundOrder])
        foundOrder++;

    if (foundOrder > maxOrder || NULL == freeLists[foundOrder]) {
        if (parent != NULL)
            return parent->alloc(s);
        throw Code::OUT_OF_MEMORY;
    }

    FreeNode* node = freeLists[foundOrder];
    removeFromFreeList(node, foundOrder);

    size_t foundSize = sizeFromOrder(foundOrder);
    atbyte* addr = (atbyte*)node - sizeof(BlockHead);

    if (foundSize > blockSize)
        addr = splitBlock(addr, foundSize, blockSize);

    BlockHead* hdr = (BlockHead*)addr;
    hdr->magic   = (size_t)0x414C4F43;
    hdr->blkSize = blockSize;
    hdr->owner   = this;

    used += blockSize;

    return addr + sizeof(BlockHead);
}

template <typename size_t> atbool MemPool<size_t>::free(atbyte *p) {
    if (NULL == p)
        return FALSE;

    BlockHead* hdr = (BlockHead*)(p - sizeof(BlockHead));

    if (hdr->owner != this)
        return hdr->owner->free(p);

    if (hdr->magic != (size_t)0x414C4F43)
        return FALSE;

    size_t blkSize = hdr->blkSize;
    atbyte* addr = (atbyte*)hdr;

    used -= blkSize;

    while (blkSize < poolSize) {
        size_t offset = (size_t)(addr - ptr);
        size_t buddyOffset = offset ^ blkSize;

        if (buddyOffset >= poolSize)
            break;

        BlockHead* buddyHdr = (BlockHead*)(ptr + buddyOffset);
        if (buddyHdr->magic != (size_t)0x46524545 || buddyHdr->blkSize != blkSize || buddyHdr->owner != this)
            break;

        atuint order = orderFromSize(blkSize);
        FreeNode* node = (FreeNode*)(ptr + buddyOffset + sizeof(BlockHead));
        removeFromFreeList(node, order);

        if (buddyOffset < offset)
            addr = ptr + buddyOffset;

        blkSize <<= 1;
    }

    addToFreeList(addr, blkSize);

    return TRUE;
}

template <typename size_t> atbool MemPool<size_t>::free(MemPool<> &subPool) {
    return free(subPool.ptr);
}

extern MemPool<>& systemPool;
extern MemPool<>& constPool;
extern MemPool<>& stringPool;

atbool initMem();

INLINE
MemPool<>& getSystemPool() { return systemPool; }

INLINE
MemPool<>& getConstPool() { return constPool; }

INLINE
MemPool<>& getStringPool() { return stringPool; }

} // end namespace atdb

#endif // AT_POOL_H
