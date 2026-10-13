#include "scn/step/enemy/sheld/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 49;
    param._c = 9e+01f;
    param._40 = 2;
    return param;
}

}}}}}  // namespace scn::step::enemy::sheld::CharaParam
