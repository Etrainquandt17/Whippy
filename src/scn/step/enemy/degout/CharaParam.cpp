#include "scn/step/enemy/degout/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._24 = 2;
    param._14 = 40;
    return param;
}

}}}}}  // namespace scn::step::enemy::degout::CharaParam
