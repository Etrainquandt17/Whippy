#ifndef G3D_MODELMULTIANIMCONTEXT_H
#define G3D_MODELMULTIANIMCONTEXT_H

#include "g3d/ResModelContext.h"
#include "hel/common/FixedString.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace g3d {

class ModelMultiAnimContext : public ResModelContext {
public:
    static hel::common::FixedString<32> DefaultHeapNamePrefix();
    static u32 DefaultOneAnimSlotWorkMemSize();
    static u32 DefaultAnimSlotNum();

    ModelMultiAnimContext(const ResModelContext& resModel, u32 animSlotNum, u32 oneAnimSlotWorkMemSize,
                          const hel::common::FixedString<32>& heapNamePrefix, mem::IAllocator& allocator);

private:
    u32 mAnimSlotNum;
    u32 mOneAnimSlotWorkMemSize;
    hel::common::FixedString<32> mHeapNamePrefix;
    mem::IAllocator& mAllocator;
};

}

#endif
