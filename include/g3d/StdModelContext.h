#ifndef G3D_STDMODELCONTEXT_H
#define G3D_STDMODELCONTEXT_H

#include "g3d/ModelContext.h"
#include "types.h"

namespace g3d {

// TODO: no constructor of this class is left in the program. Callers hand it over by reference as it is and by
// value with a copy of all 0x4C bytes, which is what a class that adds nothing to ModelContext gives; the
// constructor's arguments are assumed to be ModelContext's.
class StdModelContext : public ModelContext {
public:
    StdModelContext(const ResModelContext& resModel, const ModelBufferOption& option, u32 maxNumChildren, u32 numView,
                    mem::IAllocator& allocator, bool isCreateNodeLocalMtx)
        : ModelContext(resModel, option, maxNumChildren, numView, allocator, isCreateNodeLocalMtx) {}
};

}

#endif
