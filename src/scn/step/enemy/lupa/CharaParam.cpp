#include "scn/step/enemy/lupa/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 3;
    param._30 = 425;
    param._46 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::lupa::CharaParam
