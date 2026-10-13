#include "scn/step/enemy/mahoroalowper/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 60;
    param._2c = 0.35f;
    param._46 = false;
    param._47 = false;
    param._10 = 8;
    param._4b = true;
    param._24 = 2;
    return param;
}

}
}
}
}
}
