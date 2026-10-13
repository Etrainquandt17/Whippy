#include "scn/step/enemy/elec/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._2c = 0.3f;
    param._14 = 12;
    param._10 = 8;
    param._4d = true;
    return param;
}

}}}}}  // namespace scn::step::enemy::elec::CharaParam
