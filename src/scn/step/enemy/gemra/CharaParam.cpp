#include "scn/step/enemy/gemra/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace gemra {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 7;
    param._14 = 16;
    param._4d = true;
    return param;
}

}
}
}
}
}
