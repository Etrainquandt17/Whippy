#include "scn/step/enemy/broomhatter/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._14 = 12;
    return param;
}

}}}}}  // namespace scn::step::enemy::broomhatter::CharaParam
