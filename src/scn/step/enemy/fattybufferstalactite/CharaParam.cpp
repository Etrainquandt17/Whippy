#include "scn/step/enemy/fattybufferstalactite/CharaParam.h"

#include "hel/math/Vector2.h"
#include "scn/step/enemy/common/ParamBase.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferstalactite {
namespace CharaParam {

// TODO: enemy::CharaParam::_4 is a hel::math::Vector2 in the original, assigned from a constant here.
enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._47 = false;
    param._45 = true;
    hel::math::Vec2 v = { 0.0f, 1.5f };
    reinterpret_cast<Vector2&>(param._4) = reinterpret_cast<Vector2&>(v);
    param._2c = 0.55f;
    param._30 = 488;
    param._46 = false;
    param._4b = true;
    return param;
}

}}}}}  // namespace scn::step::enemy::fattybufferstalactite::CharaParam
