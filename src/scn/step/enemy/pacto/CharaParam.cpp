#include "scn/step/enemy/pacto/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace pacto {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, -0.1f };
    reinterpret_cast<Vector2&>(param._4) = reinterpret_cast<Vector2&>(v);
    param._c = 0.0f;
    param._24 = 1;
    param._14 = 32;
    param._2c = 0.9f;
    param._45 = true;
    param._49 = true;
    param._47 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::pacto::CharaParam
