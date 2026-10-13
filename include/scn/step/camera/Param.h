#ifndef SCN_STEP_CAMERA_PARAM_H
#define SCN_STEP_CAMERA_PARAM_H

#include "types.h"

namespace scn {
namespace step {
namespace camera {

struct Param {
    f32 _0;
    f32 _4;
    f32 _8;
    f32 _C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    u8 _20[0x74];
    f32 _94;
    f32 _98;
    f32 _9C;
    f32 _A0;
    f32 _A4;
    f32 _A8;
    f32 _AC;
    f32 _B0;
};

}}}  // namespace scn::step::camera

#endif
