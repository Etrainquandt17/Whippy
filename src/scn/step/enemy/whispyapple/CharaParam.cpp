#include "scn/step/enemy/whispyapple/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._14 = 1;
    param._2c = 0.35f;
    param._30 = 450;
    param._46 = false;
    param._47 = false;
    param._48 = false;
    param._4b = true;
    return param;
}

enemy::CharaParam CreatePoison() {
    enemy::CharaParam param = Create();
    param._24 = 2;
    return param;
}

}}}}}  // namespace scn::step::enemy::whispyapple::CharaParam
