#include "scn/step/enemy/sun/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace sun {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 0.5f };
    reinterpret_cast<hel::math::Vector2&>(param._4) = reinterpret_cast<hel::math::Vector2&>(v);
    param._c = 0.0f;
    param._34 = 2.5f;
    param._24 = 2;
    param._44 = true;
    param._47 = false;
    param._4a = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::sun::CharaParam
