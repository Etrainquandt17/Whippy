#include "scn/step/enemy/sodory/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._10 = 1;
    param._14 = 12;
    return param;
}

}}}}}  // namespace scn::step::enemy::sodory::CharaParam
