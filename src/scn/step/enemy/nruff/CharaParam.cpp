#include "scn/step/enemy/nruff/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 12;
    param._34 = 1.5f;
    return param;
}

}}}}}  // namespace scn::step::enemy::nruff::CharaParam
