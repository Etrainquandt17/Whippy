#include "scn/step/enemy/twister/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 14;
    return param;
}

}}}}}  // namespace scn::step::enemy::twister::CharaParam
