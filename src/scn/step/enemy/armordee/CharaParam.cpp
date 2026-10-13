#include "scn/step/enemy/armordee/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace armordee {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 1.2f };
    reinterpret_cast<hel::math::Vector2&>(param._4) = reinterpret_cast<hel::math::Vector2&>(v);
    param._14 = 48;
    param._18 = 60;
    param._1c = 0.3f;
    param._20 = 3;
    param._24 = 1;
    param._2c = 1.15f;
    param._45 = true;
    param._34 = 2.0f;
    param._40 = 4;
    return param;
}

}}}}}  // namespace scn::step::enemy::armordee::CharaParam
