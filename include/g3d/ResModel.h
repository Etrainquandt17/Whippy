#ifndef G3D_RESMODEL_H
#define G3D_RESMODEL_H

#include "g3d/ResFileAccessor.h"
#include "g3d/ResNode.h"
#include "nw4r/g3d/res/g3d_resmdl.h"
#include "types.h"

namespace g3d {

class ResModelContext;

class ResModel {
public:
    ResModel();
    ResModel(const ResModelContext& context);

    u32 nodeCount() const;
    ResNode nodeByIndex(u32 index) const;
    ResNode nodeByName(const char* name) const;

private:
    ResFileAccessor mFile;
    nw4r::g3d::ResMdl mObj;
};

}

#endif
