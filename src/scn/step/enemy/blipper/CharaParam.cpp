#include "scn/step/enemy/blipper/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 8;
    param._34 = 1.2f;
    return param;
}

}}}}}  // namespace scn::step::enemy::blipper::CharaParam
