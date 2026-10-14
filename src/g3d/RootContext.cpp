#include "g3d/RootContext.h"

#include "hel/common/ExplicitSingleton.h"
#include "mem/Memory.h"

using hel::common::ExplicitSingleton;

namespace g3d {

mem::IAllocator& RootContext::DefaultAllocator() {
    return ExplicitSingleton<mem::Memory>::object_->sceneHeap();
}

u32 RootContext::DefaultMaxNumChildren() {
    return 32;
}

u32 RootContext::DefaultMaxNumScnObj() {
    return 32;
}

u32 RootContext::DefaultNumLightObj() {
    return 8;
}

u32 RootContext::DefaultNumLightSet() {
    return 1;
}

RootContext::RootContext(mem::IAllocator& allocator, u32 maxNumChildren, u32 maxNumScnObj, u32 numLightObj, u32 numLightSet)
    : mAllocator(&allocator)
    , mMaxNumChildren(maxNumChildren)
    , mMaxNumScnObj(maxNumScnObj)
    , mNumLightObj(numLightObj)
    , mNumLightSet(numLightSet) {}

}  // namespace g3d
