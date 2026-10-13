#include "g3d/ModelAnimContext.h"

namespace g3d {

ModelAnimContext::ModelAnimContext(const ResModelContext& resModel, mem::IAllocator& charaAllocator, mem::IAllocator& colorAllocator,
                                   mem::IAllocator& shapeAllocator, mem::IAllocator& texPatternAllocator,
                                   mem::IAllocator& texSRTAllocator, mem::IAllocator& visibleAllocator)
    : ResModelContext(resModel)
    , mCharaAllocator(charaAllocator)
    , mColorAllocator(colorAllocator)
    , mShapeAllocator(shapeAllocator)
    , mTexPatternAllocator(texPatternAllocator)
    , mTexSRTAllocator(texSRTAllocator)
    , mVisibleAllocator(visibleAllocator) {}

}  // namespace g3d
