#include "scn/step/enemy/knucklejoe/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 21;
    param._14 = 24;
    return param;
}

}}}}}  // namespace scn::step::enemy::knucklejoe::CharaParam
