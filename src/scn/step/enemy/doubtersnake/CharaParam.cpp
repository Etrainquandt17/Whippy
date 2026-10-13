#include "scn/step/enemy/doubtersnake/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 8;
    param._30 = 408;
    return param;
}

enemy::CharaParam CreateYellow() {
    enemy::CharaParam param = Create();
    param._14 = 12;
    return param;
}

}}}}}  // namespace scn::step::enemy::doubtersnake::CharaParam
