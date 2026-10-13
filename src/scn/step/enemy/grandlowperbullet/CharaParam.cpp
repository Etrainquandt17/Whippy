#include "scn/step/enemy/grandlowperbullet/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._14 = 1;
    param._47 = false;
    param._30 = 470;
    param._4b = true;
    param._46 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::grandlowperbullet::CharaParam
