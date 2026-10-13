#include "scn/step/enemy/rocky/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 42;
    param._10 = 9;
    return param;
}

}}}}}  // namespace scn::step::enemy::rocky::CharaParam
