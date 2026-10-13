#ifndef G3D_FOGACCESSOR_H
#define G3D_FOGACCESSOR_H

#include "nw4r/g3d/g3d_fog.h"
#include "types.h"

namespace g3d {

class FogAccessor : public nw4r::g3d::Fog {
public:
    FogAccessor(const nw4r::g3d::Fog& fog);

    void setFogType(GXFogType type);
    void setZ(f32 startZ, f32 endZ);
    void setFogColor(GXColor color);
    void setFogRangeAdj(bool enable);

private:
    bool _4;
};

}  // namespace g3d

#endif
