#include "scn/step/enemy/strikeboxbullet/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace strikeboxbullet {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._4.x = 0.0f;
    param._4.y = 0.0f;
    param._47 = false;
    param._2c = 1.0f;
    param._30 = 470;
    param._10 = 18;
    return param;
}

}}}}}  // namespace scn::step::enemy::strikeboxbullet::CharaParam
