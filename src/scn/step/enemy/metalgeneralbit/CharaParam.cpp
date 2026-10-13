#include "scn/step/enemy/metalgeneralbit/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._45 = true;
    hel::math::Vec2 v = { 0.0f, 0.4f };
    reinterpret_cast<hel::math::Vector2&>(param._4) = reinterpret_cast<hel::math::Vector2&>(v);
    param._2c = 0.25f;
    param._47 = false;
    param._10 = 7;
    return param;
}

}}}}}  // namespace scn::step::enemy::metalgeneralbit::CharaParam
