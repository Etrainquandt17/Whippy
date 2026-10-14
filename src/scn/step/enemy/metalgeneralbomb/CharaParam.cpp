#include "scn/step/enemy/metalgeneralbomb/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbomb {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._10 = 15;
    param._47 = false;
    param._45 = true;
    hel::math::Vec2 v = { 0.0f, 0.1f };
    reinterpret_cast<Vector2&>(param._4) = reinterpret_cast<Vector2&>(v);
    param._2c = 0.2f;
    param._34 = 0.5f;
    param._30 = 478;
    param._4b = true;
    param._46 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::metalgeneralbomb::CharaParam
