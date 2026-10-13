#include "scn/step/enemy/bladeknight/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 1;
    param._14 = 16;
    param._3c = 13;
    return param;
}

}}}}}  // namespace scn::step::enemy::bladeknight::CharaParam
