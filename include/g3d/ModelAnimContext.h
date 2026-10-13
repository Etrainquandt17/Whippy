#ifndef G3D_MODELANIMCONTEXT_H
#define G3D_MODELANIMCONTEXT_H

#include "g3d/ResModelContext.h"

namespace mem {
class IAllocator;
}

namespace g3d {

class ModelAnimContext : public ResModelContext {
public:
    ModelAnimContext(const ResModelContext& resModel, mem::IAllocator& charaAllocator, mem::IAllocator& colorAllocator,
                     mem::IAllocator& shapeAllocator, mem::IAllocator& texPatternAllocator, mem::IAllocator& texSRTAllocator,
                     mem::IAllocator& visibleAllocator);

private:
    mem::IAllocator& mCharaAllocator;
    mem::IAllocator& mColorAllocator;
    mem::IAllocator& mShapeAllocator;
    mem::IAllocator& mTexPatternAllocator;
    mem::IAllocator& mTexSRTAllocator;
    mem::IAllocator& mVisibleAllocator;
};

}

#endif
