#include "scn/step/enemy/mahoroahammer/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroahammer {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 32;
    param._46 = false;
    param._10 = 17;
    param._c = 0.0f;
    return param;
}

}}}}}  // namespace scn::step::enemy::mahoroahammer::CharaParam
