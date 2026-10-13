#include "g3d/FogAccessor.h"

namespace g3d {

FogAccessor::FogAccessor(const nw4r::g3d::Fog& fog)
    : nw4r::g3d::Fog(fog)
    , _4(true) {}

void FogAccessor::setFogType(GXFogType type) {
    SetFogType(type);
}

void FogAccessor::setZ(f32 startZ, f32 endZ) {
    SetZ(startZ, endZ);
}

void FogAccessor::setFogColor(GXColor color) {
    SetFogColor(color);
}

void FogAccessor::setFogRangeAdj(bool enable) {
    SetFogRangeAdj(enable);
}

}
