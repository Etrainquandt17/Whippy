#ifndef MINTVM_STLALLOCATOR_H
#define MINTVM_STLALLOCATOR_H

#include "mintvm/IAllocator.h"
#include "mintvm/MintSetting.h"
#include "types.h"

namespace mintvm {

template <class T>
class STLAllocator {
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef unsigned long size_type;
    typedef long difference_type;

    template <class U>
    struct rebind {
        typedef STLAllocator<U> other;
    };

    STLAllocator() : mAllocator(&ExplicitSingleton<MintSetting>::Instance()->mVMAllocator) {}

    template <class U>
    STLAllocator(const STLAllocator<U>& other) : mAllocator(other.mAllocator) {}

    ~STLAllocator() {}

    pointer allocate(size_type count) {
        return static_cast<pointer>(mAllocator->mintAlloc(count * sizeof(T)));
    }

    void deallocate(const_pointer ptr, size_type) {
        mAllocator->mintFree(const_cast<pointer>(ptr));
    }

    IAllocator* mAllocator;
};

}  // namespace mintvm

#endif
