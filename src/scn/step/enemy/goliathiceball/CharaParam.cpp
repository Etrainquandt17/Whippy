#include "scn/step/enemy/goliathiceball/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._2c = 0.35f;
    param._30 = 493;
    param._46 = false;
    param._47 = false;
    param._10 = 18;
    param._4b = true;
    return param;
}

}}}}}  // namespace scn::step::enemy::goliathiceball::CharaParam
