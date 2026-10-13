#ifndef MINTVM_RNOBJECT_H
#define MINTVM_RNOBJECT_H

#include "mintvm/IAllocator.h"
#include "mintvm/MintSetting.h"
#include "types.h"

namespace mintvm {

class RNObject {
public:
    virtual ~RNObject() {}

    static IAllocator& allocator() {
        return ExplicitSingleton<MintSetting>::Instance()->mRunAllocator;
    }

    static void* operator new(u32 size) {
        return allocator().mintAlloc(size);
    }

    static void operator delete(void* ptr) {
        allocator().mintFree(ptr);
    }
};

}  // namespace mintvm

#endif
