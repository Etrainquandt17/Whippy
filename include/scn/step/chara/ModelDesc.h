#ifndef SCN_STEP_CHARA_MODELDESC_H
#define SCN_STEP_CHARA_MODELDESC_H

#include "gobj/ModelDesc.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: members.
class ModelDesc {
public:
    ModelDesc();

    u32 _0;
    const char* _4;
    const char* _8;
    hel::math::Vector3 _c;
    gobj::ModelDesc mModel;
    u32 _70[4];
};

}
}
}

#endif
