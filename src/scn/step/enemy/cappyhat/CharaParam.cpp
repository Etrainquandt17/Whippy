#include "scn/step/enemy/cappyhat/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace cappyhat {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 0.0f };
    reinterpret_cast<Vector2&>(param._4) = reinterpret_cast<Vector2&>(v);
    param._2c = 0.4f;
    param._14 = 1;
    param._47 = false;
    param._46 = false;
    param._4b = true;
    return param;
}

}}}}}  // namespace scn::step::enemy::cappyhat::CharaParam
