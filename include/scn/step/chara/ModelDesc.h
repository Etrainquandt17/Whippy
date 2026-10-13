#ifndef SCN_STEP_CHARA_MODELDESC_H
#define SCN_STEP_CHARA_MODELDESC_H

#include "gobj/ModelDesc.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace dynamics {
class Desc;
}

namespace scn {
namespace step {
namespace chara {

// TODO: members.
class ModelDesc {
public:
    // TODO: the pointer at 0x7C is to one of these; mDescs is a hel::common::Array<dynamics::Desc, N>.
    struct DynamicsDesc {
        u32 mNum;
        dynamics::Desc* mDescs;
    };

    ModelDesc();

    u32 _0;
    const char* _4;
    const char* _8;
    hel::math::Vector3 _c;
    gobj::ModelDesc mModel;
    u32 _70[4];
};

}}}  // namespace scn::step::chara

#endif
