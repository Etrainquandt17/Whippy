#include "scn/step/enemy/mahoroamagicball/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 48;
    param._2c = 0.35f;
    param._30 = 508;
    param._46 = false;
    param._47 = false;
    param._4b = true;
    return param;
}

}
}
}
}
}
