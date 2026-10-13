#include "scn/step/enemy/wapod/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 3e+01f;
    param._2c = 0.4f;
    param._14 = 8;
    return param;
}

}}}}}  // namespace scn::step::enemy::wapod::CharaParam
