#include "scn/step/enemy/mopoo/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._40 = 2;
    return param;
}

}}}}}  // namespace scn::step::enemy::mopoo::CharaParam
