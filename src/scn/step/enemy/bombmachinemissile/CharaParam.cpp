#include "scn/step/enemy/bombmachinemissile/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace bombmachinemissile {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 15;
    param._c = 9e+01f;
    param._47 = false;
    param._30 = 470;
    return param;
}

}}}}}  // namespace scn::step::enemy::bombmachinemissile::CharaParam
