#include "scn/step/enemy/lowperbullet/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {
namespace CharaParam {

enemy::CharaParam CreateBase() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._47 = false;
    param._4b = true;
    param._46 = false;
    return param;
}

enemy::CharaParam CreateLv1() {
    enemy::CharaParam param = CreateBase();
    param._14 = 1;
    param._30 = 441;
    return param;
}

enemy::CharaParam CreateLv2() {
    enemy::CharaParam param = CreateBase();
    param._14 = 8;
    param._30 = 442;
    return param;
}

enemy::CharaParam CreateLv3() {
    enemy::CharaParam param = CreateBase();
    param._14 = 12;
    param._30 = 443;
    return param;
}

enemy::CharaParam CreateLv4() {
    enemy::CharaParam param = CreateBase();
    param._14 = 16;
    param._30 = 444;
    return param;
}

}}}}}  // namespace scn::step::enemy::lowperbullet::CharaParam
