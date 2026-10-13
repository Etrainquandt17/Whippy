#include "scn/step/enemy/flamer/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace flamer {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 12;
    param._c = 0.0f;
    param._2c = 0.3f;
    param._10 = 5;
    return param;
}

}}}}}  // namespace scn::step::enemy::flamer::CharaParam
