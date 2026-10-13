#include "scn/step/enemy/whippy/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace whippy {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 4;
    param._c = 3e+01f;
    return param;
}

}}}}}  // namespace scn::step::enemy::whippy::CharaParam
