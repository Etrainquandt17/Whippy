#include "scn/step/enemy/bouncy/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 12;
    return param;
}

}}}}}  // namespace scn::step::enemy::bouncy::CharaParam
