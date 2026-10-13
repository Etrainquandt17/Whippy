#include "scn/step/enemy/como/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 0.65f };
    param._4.x = v.x;
    param._4.y = v.y;
    param._c = 0.0f;
    param._2c = 0.45f;
    param._47 = false;
    param._14 = 8;
    param._4b = true;
    return param;
}

}
}
}
}
}
