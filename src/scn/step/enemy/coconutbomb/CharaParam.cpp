#include "scn/step/enemy/coconutbomb/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace coconutbomb {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 0.45f };
    reinterpret_cast<Vector2&>(param._4) = reinterpret_cast<Vector2&>(v);
    param._14 = 1;
    param._30 = 413;
    param._46 = false;
    param._47 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::coconutbomb::CharaParam
