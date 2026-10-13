#include "scn/step/enemy/brontoburt/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 8;
    param._0 = 0.95f;
    return param;
}

}}}}}  // namespace scn::step::enemy::brontoburt::CharaParam
