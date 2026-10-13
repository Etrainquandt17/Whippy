#include "gobj/MoveParam.h"

namespace gobj {

MoveParamAccel MoveParamAccel::Zero() {
    return Create(0.0f, 0.0f, 0.0f);
}

MoveParamAccel MoveParamAccel::Create(f32 _0, f32 _4, f32 _8) {
    MoveParamAccel param = {};
    param._0 = _0;
    param._4 = _4;
    param._8 = _8;
    return param;
}

}  // namespace gobj
