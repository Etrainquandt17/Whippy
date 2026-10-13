#ifndef G3D_MODELCONTEXT_H
#define G3D_MODELCONTEXT_H

#include "g3d/ModelBufferOption.h"
#include "g3d/ResModelContext.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace g3d {

class StdModelContext;

class ModelContext : public ResModelContext {
public:
    ModelContext(const ResModelContext& resModel, const ModelBufferOption& option, u32 maxNumChildren, u32 numView, mem::IAllocator& allocator,
                 bool isCreateNodeLocalMtx);

    static mem::IAllocator& DefaultAllocator();
    static ModelBufferOption DefaultModelBufferOption();
    static u32 DefaultMaxNumChildren();
    static u32 DefaultNumView();
    static bool DefaultIsCreateNodeLocalMtx();

    // TODO: StdModelContext most likely derives from this class and is what the callers of StdModel build.
    // Until g3d/StdModelContext.h says so, this lets them hand over a ModelContext as it is.
    operator const StdModelContext&() const { return reinterpret_cast<const StdModelContext&>(*this); }

private:
    ModelBufferOption mOption;
    u32 mMaxNumChildren;
    u32 mNumView;
    mem::IAllocator& mAllocator;
    bool mIsCreateNodeLocalMtx;
};

}  // namespace g3d

#endif
