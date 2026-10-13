#include "scn/step/enemy/goliathicicle/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathicicle {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._4.y = 1.1f;
    param._c = 0.0f;
    param._14 = 1;
    param._2c = 0.49f;
    param._30 = 494;
    param._46 = false;
    param._47 = false;
    param._10 = 18;
    param._4b = true;
    return param;
}

}
}
}
}
}
