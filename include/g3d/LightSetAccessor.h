#ifndef G3D_LIGHTSETACCESSOR_H
#define G3D_LIGHTSETACCESSOR_H

#include "nw4r/g3d/g3d_light.h"
#include "types.h"

namespace g3d {

class LightSetAccessor : public nw4r::g3d::LightSet {
public:
    LightSetAccessor();
    LightSetAccessor(const nw4r::g3d::LightSet& lightSet);

    bool isValid() const;
    void enableLightObj(u32 lightIndex, u32 lightObjIndex) const;
    void disableLightObj(u32 lightIndex) const;
    void disableLightObjAll() const;
    void enableAmbientLightObj(u32 lightObjIndex) const;
    void disableAmbientLightObj() const;
    void setLightObj(u32 lightIndex, const nw4r::g3d::LightObj& lightObj) const;
    void setAmbientLightObj(const nw4r::g3d::AmbLightObj& lightObj) const;
};

}  // namespace g3d

#endif
