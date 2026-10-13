#include "scn/step/enemy/fattybufferjr/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._30 = 487;
    return param;
}

}}}}}  // namespace scn::step::enemy::fattybufferjr::CharaParam
