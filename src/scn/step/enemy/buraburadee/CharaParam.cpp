#include "scn/step/enemy/buraburadee/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace buraburadee {
namespace CharaParam {

enemy::CharaParam CreateDee() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 12;
    return param;
}

enemy::CharaParam CreateDoo() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 7;
    param._14 = 18;
    return param;
}

}}}}}  // namespace scn::step::enemy::buraburadee::CharaParam
