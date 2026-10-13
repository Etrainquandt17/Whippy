#ifndef MINTVM_VMOBJECT_H
#define MINTVM_VMOBJECT_H

#include "mintvm/IAllocator.h"
#include "mintvm/MintSetting.h"
#include "mintvm/NonCopyable.h"
#include "types.h"

namespace mintvm {

class VMObject : public NonCopyable {
public:
    VMObject() {}
    virtual ~VMObject() {}

    // The local keeps this a call where a unit uses it more than once.
    static IAllocator& allocator() {
        MintSetting* setting = ExplicitSingleton<MintSetting>::Instance();
        return setting->mVMAllocator;
    }

    static void* operator new(u32 size) {
        return allocator().mintAlloc(size);
    }

    static void operator delete(void* ptr) {
        allocator().mintFree(ptr);
    }
};

}

#endif
