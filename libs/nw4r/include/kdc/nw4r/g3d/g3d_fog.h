#ifndef NW4R_G3D_FOG_H
#define NW4R_G3D_FOG_H
#include <kdc/nw4r/types_nw4r.h>

#include "kdc/nw4r/g3d/res/g3d_rescommon.h"

#include "kdc/nw4r/math.h" // IWYU pragma: export
#include "kdc/nw4r/ut.h"   // IWYU pragma: export

#include "kdc/revolution/GX.h" // IWYU pragma: export

namespace nw4r {
namespace g3d {

struct FogData {
    GXFogType type;         // at 0x0
    f32 startz;             // at 0x4
    f32 endz;               // at 0x8
    f32 nearz;              // at 0xC
    f32 farz;               // at 0x10
    GXColor color;          // at 0x14
    GXBool adjEnable;       // at 0x18
    u8 PADDING_0x19;        // at 0x19
    u16 adjCenter;          // at 0x1A
    GXFogAdjTable adjTable; // at 0x1C
};

class Fog : public ResCommon<FogData> {
public:
    // NOTE: Is merged into nw4r::g3d::Camera::Camera(nw4r::g3d::CameraData*)
    explicit Fog(FogData *pData);

    void Init();
    Fog CopyTo(void *pDst) const;

    void SetFogRangeAdjParam(u16 width, u16 center, const math::MTX44 &rProjMtx);
    void SetGP() const;

    //Here since pointer assert doesn't happen here (assert seems to be linked to rescommon)
    FogData &ref() {
        return *ptr();
    }

    const FogData &ref() const {
        return *ptr();
    }

    //TODO: Assert Version doesn't inline
    void SetFogType(GXFogType type) {
        NW4RAssert_Line(65, IsValid());
        if (!IsValid()) {
            return;
        }

        ref().type = type;
    }

    //TODO: Assert Version doesn't inline
    inline void SetZ(f32 startZ, f32 endZ) {
        NW4RAssert_Line(75, IsValid());
        if (!IsValid()) {
            return;
        }

        FogData &r = ref();

        r.startz = startZ;
        r.endz = endZ;
    }

    void SetNearFar(f32 nearZ, f32 farZ) {
        if (!IsValid()) {
            return;
        }

        FogData &r = ref();

        r.nearz = nearZ;
        r.farz = farZ;
    }

    //TODO: Inlining issues in FogAccessor (Donut)
    void SetFogColor(GXColor color) {
        NW4RAssert_Line(99, IsValid());
        if (!IsValid()) {
            return;
        }

        ref().color = color;
    }

    bool IsFogRangeAdjEnable() const {
        return IsValid() && ref().adjEnable == TRUE;
    }

    void SetFogRangeAdj(bool enable) {
        NW4RAssert_Line(117, IsValid());
        if (!IsValid()) {
            return;
        }
        ref().adjEnable = enable;
    }
};

} // namespace g3d
} // namespace nw4r

#endif
