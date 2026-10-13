#include "scn/step/enemy/mumbies/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._24 = 2;
    return param;
}

}}}}}  // namespace scn::step::enemy::mumbies::CharaParam
