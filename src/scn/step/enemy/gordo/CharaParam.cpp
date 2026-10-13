#include "scn/step/enemy/gordo/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._24 = 2;
    param._44 = true;
    param._2c = 0.4f;
    param._30 = 569;
    param._47 = false;
    return param;
}

}}}}}  // namespace scn::step::enemy::gordo::CharaParam
