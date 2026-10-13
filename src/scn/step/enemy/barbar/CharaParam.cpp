#include "scn/step/enemy/barbar/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._44 = true;
    param._45 = true;
    param._14 = 12;
    return param;
}

}
}
}
}
}
