#include "g3d/LightSetAccessor.h"

namespace g3d {

bool LightSetAccessor::isValid() const {
    return IsValid();
}

void LightSetAccessor::enableLightObj(u32 lightIndex, u32 lightObjIndex) const {
    const_cast<LightSetAccessor*>(this)->SelectLightObj(lightIndex, lightObjIndex);
}

void LightSetAccessor::disableLightObj(u32 lightIndex) const {
    const_cast<LightSetAccessor*>(this)->SelectLightObj(lightIndex, -1);
}

void LightSetAccessor::disableLightObjAll() const {
    for (u32 i = 0; i < 8; i++) {
        disableLightObj(i);
    }
}

void LightSetAccessor::enableAmbientLightObj(u32 lightObjIndex) const {
    const_cast<LightSetAccessor*>(this)->SelectAmbLightObj(lightObjIndex);
}

void LightSetAccessor::disableAmbientLightObj() const {
    const_cast<LightSetAccessor*>(this)->SelectAmbLightObj(-1);
}

void LightSetAccessor::setLightObj(u32 lightIndex, const nw4r::g3d::LightObj& lightObj) const {
    *const_cast<LightSetAccessor*>(this)->GetLightObj(lightIndex) = lightObj;
}

void LightSetAccessor::setAmbientLightObj(const nw4r::g3d::AmbLightObj& lightObj) const {
    *const_cast<LightSetAccessor*>(this)->GetAmbLightObj() = lightObj;
}

}  // namespace g3d
