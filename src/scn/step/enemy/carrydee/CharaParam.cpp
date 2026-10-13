#include "scn/step/enemy/carrydee/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._2c = 0.48f;
    param._14 = 1;
    return param;
}

}
}
}
}
}
