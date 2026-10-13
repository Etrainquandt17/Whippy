#ifndef G3D_ROOTCONTEXT_H
#define G3D_ROOTCONTEXT_H

#include "types.h"

namespace mem {
class IAllocator;
}

namespace g3d {

class RootContext {
public:
    static mem::IAllocator& DefaultAllocator();
    static u32 DefaultMaxNumChildren();
    static u32 DefaultMaxNumScnObj();
    static u32 DefaultNumLightObj();
    static u32 DefaultNumLightSet();

    RootContext(mem::IAllocator& allocator, u32 maxNumChildren, u32 maxNumScnObj, u32 numLightObj, u32 numLightSet);

private:
    mem::IAllocator* mAllocator;
    u32 mMaxNumChildren;
    u32 mMaxNumScnObj;
    u32 mNumLightObj;
    u32 mNumLightSet;
};

}

#endif
