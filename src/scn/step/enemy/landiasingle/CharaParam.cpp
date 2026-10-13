#include "scn/step/enemy/landiasingle/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._47 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::landiasingle::CharaParam
