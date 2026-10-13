#include "scn/step/enemy/zankibblecutter/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace zankibblecutter {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._24 = 1;
    param._47 = false;
    param._10 = 2;
    hel::math::Vec2 v = { 0.0f, 0.0f };
    reinterpret_cast<hel::math::Vector2&>(param._4) = reinterpret_cast<hel::math::Vector2&>(v);
    param._4b = true;
    param._46 = false;
    return param;
}

}
}
}
}
}
