#include "scn/step/enemy/sirkibble/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 2;
    param._0 = 0.95f;
    param._14 = 20;
    return param;
}

}}}}}  // namespace scn::step::enemy::sirkibble::CharaParam
