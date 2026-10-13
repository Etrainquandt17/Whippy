#ifndef G3D_CHARAMODELCONTEXT_H
#define G3D_CHARAMODELCONTEXT_H

#include "g3d/ModelBufferOption.h"
#include "g3d/ResModelContext.h"
#include "hel/common/FixedString.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace g3d {

class CharaModelContext {
public:
    CharaModelContext(const ResModelContext& resModel, const ModelBufferOption& option, u32, u32 numView, u32, mem::IAllocator& allocator, bool,
                      u32 oneAnimSlotWorkMemSize, const hel::common::FixedString<32>& name);

    static u32 DefaultNumView();
    static ModelBufferOption DefaultModelBufferOption();
    static u32 DefaultOneAnimSlotWorkMemSize();

private:
    ResModelContext mResModel;
    ModelBufferOption mOption;
    u32 _3C;
    u32 mNumView;
    u32 _44;
    mem::IAllocator* mAllocator;
    bool _4C;
    u32 mOneAnimSlotWorkMemSize;
    hel::common::FixedString<32> mName;
};

}

#endif
