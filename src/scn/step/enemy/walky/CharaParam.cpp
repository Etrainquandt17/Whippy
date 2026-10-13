#include "scn/step/enemy/walky/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._0 = 1.05f;
    param._10 = 23;
    param._14 = 12;
    return param;
}

}}}}}  // namespace scn::step::enemy::walky::CharaParam
