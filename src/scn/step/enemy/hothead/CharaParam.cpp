#include "scn/step/enemy/hothead/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace hothead {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 5;
    param._3c = 8;
    param._4d = true;
    return param;
}

}
}
}
}
}
