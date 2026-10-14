#include "scn/step/enemy/leaper/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace leaper {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 1.7f };
    reinterpret_cast<Vector2&>(param._4) = reinterpret_cast<Vector2&>(v);
    param._14 = 20;
    param._2c = 1.3f;
    param._30 = 425;
    param._46 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::leaper::CharaParam
