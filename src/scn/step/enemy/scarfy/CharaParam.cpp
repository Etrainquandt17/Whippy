#include "scn/step/enemy/scarfy/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._24 = 2;
    param._14 = 12;
    return param;
}

}}}}}  // namespace scn::step::enemy::scarfy::CharaParam
