#include "scn/step/enemy/fattybufferwater/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferwater {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._10 = 12;
    param._47 = false;
    param._45 = true;
    param._30 = 486;
    param._4b = true;
    return param;
}

}}}}}  // namespace scn::step::enemy::fattybufferwater::CharaParam
