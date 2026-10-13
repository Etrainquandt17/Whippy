#ifndef NW4R_G3D_FOG_H
#define NW4R_G3D_FOG_H

#include "nw4r/g3d/res/g3d_rescommon.h"
#include "nw4r/math/math_types.h"
#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace nw4r {
namespace g3d {

struct FogData {
    GXFogType type;
    f32 startz;
    f32 endz;
    f32 nearz;
    f32 farz;
    GXColor color;
    GXBool adjEnable;
    u8 PADDING_0x19;
    u16 adjCenter;
    GXFogAdjTable adjTable;
};

class Fog : public ResCommon<FogData> {
public:
    explicit Fog(FogData* pData);

    void Init();
    Fog CopyTo(void* pDst) const;
    void SetFogRangeAdjParam(u16 width, u16 center, const math::MTX44& rProjMtx);
    void SetGP() const;

    FogData& ref() { return *ptr(); }
    const FogData& ref() const { return *ptr(); }

    void SetFogType(GXFogType type) {
        NW4R_ASSERT_AT("g3d_fog.h", 65, IsValid());
        if (!IsValid()) {
            return;
        }
        ref().type = type;
    }

    void SetZ(f32 startZ, f32 endZ) {
        NW4R_ASSERT_AT("g3d_fog.h", 75, IsValid());
        if (!IsValid()) {
            return;
        }
        FogData& r = ref();
        r.startz = startZ;
        r.endz = endZ;
    }

    void SetFogColor(GXColor color) {
        NW4R_ASSERT_AT("g3d_fog.h", 99, IsValid());
        if (!IsValid()) {
            return;
        }
        ref().color = color;
    }

    void SetFogRangeAdj(bool enable) {
        NW4R_ASSERT_AT("g3d_fog.h", 117, IsValid());
        if (!IsValid()) {
            return;
        }
        ref().adjEnable = enable;
    }
};

}
}

#endif
