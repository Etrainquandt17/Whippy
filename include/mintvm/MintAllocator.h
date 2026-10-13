#ifndef MINTVM_MINTALLOCATOR_H
#define MINTVM_MINTALLOCATOR_H

#include "mintvm/IAllocator.h"
#include "mintvm/MintAssert.h"

namespace mintvm {

class MintAllocator : public IAllocator {
public:
    typedef void* (*AllocFunction)(u32 size);
    typedef void (*FreeFunction)(void* ptr);

    MintAllocator()
        : mAlloc(0)
        , mFree(0) {}

    virtual void* mintAlloc(u32 size) {
        MINT_ASSERT("MintAllocator.hpp", 34, mAlloc);
        return mAlloc(size);
    }

    virtual void mintFree(void* ptr) {
        MINT_ASSERT("MintAllocator.hpp", 40, mFree);
        mFree(ptr);
    }

    void set(AllocFunction alloc, FreeFunction free) {
        mAlloc = alloc;
        mFree = free;
    }

    void verify() {
        MINT_ASSERT("MintAllocator.hpp", 46, mAlloc);
        MINT_ASSERT("MintAllocator.hpp", 47, mFree);
    }

    AllocFunction mAlloc;
    FreeFunction mFree;
};

}  // namespace mintvm

#endif
