#ifndef NW4R_G3D_LIGHT_H
#define NW4R_G3D_LIGHT_H

#include "nw4r/math/math_types.h"
#include "revolution/gx/GXEnum.h"
#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace nw4r {
namespace g3d {

class LightObj {
public:
    LightObj() : mFlag(0) {}
    ~LightObj() {}

    LightObj& operator=(const LightObj& rOther);

    operator GXLightObj*() { return &mObj; }
    operator const GXLightObj*() const { return &mObj; }

    void Clear();
    void InitLightColor(GXColor color);
    void InitLightPos(f32 x, f32 y, f32 z);
    void InitLightDir(f32 nx, f32 ny, f32 nz);
    void InitSpecularDir(f32 nx, f32 ny, f32 nz);
    void InitLightSpot(f32 cutoff, GXSpotFn spotFn);
    void InitLightAttnA(f32 aa, f32 ab, f32 ac);
    void InitLightDistAttn(f32 distance, f32 brightness, GXDistAttnFn distAttnFn);
    void InitLightAttnK(f32 ka, f32 kb, f32 kc);
    void InitLightShininess(f32 shininess);
    void GetLightPos(math::VEC3* pPos) const;
    void GetLightDir(math::VEC3* pDir) const;
    void ApplyViewMtx(const math::MTX34& rCamera);

    void Enable() { mFlag |= FLAG_ENABLE_LIGHT; }
    void Disable() { mFlag &= ~FLAG_ENABLE_LIGHT; }
    bool IsEnable() const { return (mFlag & FLAG_ENABLE_LIGHT) ? true : false; }

private:
    enum LightObjFlag {
        FLAG_SPOT = (1 << 0),
        FLAG_SPECULAR = (1 << 1),
        FLAG_ENABLE_LIGHT = (1 << 2),
        FLAG_SPECULAR_DIR = (1 << 3),
        FLAG_DISABLE_COLOR = (1 << 4),
        FLAG_DISABLE_ALPHA = (1 << 5)
    };

    u32 mFlag;
    GXLightObj mObj;
};

struct AmbLightObj {
    u8 r, g, b, a;
};

struct LightSetData {
    s8 idxLight[8];
    s8 idxAmbLight;
    u8 PADDING_0x9[0xC - 0x9];
};

class LightSetting;

class LightSet {
public:
    LightSet(LightSetting* pSetting, LightSetData* pData) : mpSetting(pSetting), mpLightSetData(pData) {}

    bool IsValid() const { return mpSetting != 0 && mpLightSetData != 0; }

    LightObj* GetLightObj(u32 lightIdx);
    AmbLightObj* GetAmbLightObj();
    bool SelectLightObj(u32 lightIdx, int lightObjIdx);
    bool SelectAmbLightObj(int lightObjIdx);

private:
    LightSetting* mpSetting;
    LightSetData* mpLightSetData;
};

}}  // namespace nw4r::g3d

#endif
