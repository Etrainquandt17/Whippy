#include "scn/step/enemy/parasol/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasol {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._10 = 11;
    param._47 = false;
    param._46 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::parasol::CharaParam
