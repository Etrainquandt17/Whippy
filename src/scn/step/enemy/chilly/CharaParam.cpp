#include "scn/step/enemy/chilly/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 18;
    param._14 = 12;
    param._3c = 10;
    return param;
}

}}}}}  // namespace scn::step::enemy::chilly::CharaParam
