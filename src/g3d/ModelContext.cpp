#include "g3d/ModelContext.h"

#include "hel/common/ExplicitSingleton.h"
#include "mem/Memory.h"

namespace g3d {

mem::IAllocator& ModelContext::DefaultAllocator() {
    return hel::common::ExplicitSingleton<mem::Memory>::object_->sceneHeap();
}

ModelBufferOption ModelContext::DefaultModelBufferOption() {
    ModelBufferOption option;
    option.addAnimMatColor();
    option.addAnimTexPattern();
    option.addAnimTexSRT();
    option.addAnimVisible();
    option._B = true;
    option._4 = true;
    option._5 = true;
    return option;
}

ModelContext::ModelContext(const ResModelContext& resModel, const ModelBufferOption& option, u32 maxNumChildren, u32 numView,
                           mem::IAllocator& allocator, bool isCreateNodeLocalMtx)
    : ResModelContext(resModel)
    , mOption(option)
    , mMaxNumChildren(maxNumChildren)
    , mNumView(numView)
    , mAllocator(allocator)
    , mIsCreateNodeLocalMtx(isCreateNodeLocalMtx) {}

u32 ModelContext::DefaultMaxNumChildren() {
    return 4;
}

u32 ModelContext::DefaultNumView() {
    return 2;
}

bool ModelContext::DefaultIsCreateNodeLocalMtx() {
    return true;
}

}  // namespace g3d
