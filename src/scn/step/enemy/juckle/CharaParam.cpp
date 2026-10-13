#include "scn/step/enemy/juckle/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace juckle {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 90.0f;
    param._4.y += 0.2f;
    param._14 = 8;
    param._10 = 2;
    return param;
}

}}}}}  // namespace scn::step::enemy::juckle::CharaParam
