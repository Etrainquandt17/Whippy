#include "scn/step/enemy/aquarock/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace aquarock {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    hel::math::Vec2 v = { 0.0f, 0.5f };
    param._4.x = v.x;
    param._4.y = v.y;
    param._24 = 2;
    param._44 = true;
    param._47 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::aquarock::CharaParam
