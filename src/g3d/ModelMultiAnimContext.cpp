#include "g3d/ModelMultiAnimContext.h"

using hel::common::FixedString;
using hel::common::FixedStringIN;

namespace g3d {

FixedString<32> ModelMultiAnimContext::DefaultHeapNamePrefix() {
    return FixedStringIN<char, 32>::FromFormat("%s", "MdlAnm");
}

u32 ModelMultiAnimContext::DefaultOneAnimSlotWorkMemSize() {
    return 0x2000;
}

ModelMultiAnimContext::ModelMultiAnimContext(const ResModelContext& resModel, u32 animSlotNum, u32 oneAnimSlotWorkMemSize,
                                             const FixedString<32>& heapNamePrefix, mem::IAllocator& allocator)
    : ResModelContext(resModel)
    , mAnimSlotNum(animSlotNum)
    , mOneAnimSlotWorkMemSize(oneAnimSlotWorkMemSize)
    , mHeapNamePrefix(heapNamePrefix)
    , mAllocator(allocator) {}

u32 ModelMultiAnimContext::DefaultAnimSlotNum() {
    return 2;
}

}  // namespace g3d
