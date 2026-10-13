#include "scn/step/enemy/dubiorjr/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 9e+01f;
    param._14 = 1;
    param._47 = false;
    param._10 = 8;
    param._30 = 427;
    param._46 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::dubiorjr::CharaParam
