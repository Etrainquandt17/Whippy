#include "scn/step/enemy/goliathsnowball/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathsnowball {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 0.75f };
    reinterpret_cast<hel::math::Vector2&>(param._4) = reinterpret_cast<hel::math::Vector2&>(v);
    param._14 = 1;
    param._2c = 0.35f;
    param._30 = 492;
    param._46 = false;
    param._47 = false;
    param._10 = 18;
    param._4b = true;
    return param;
}

}
}
}
}
}
