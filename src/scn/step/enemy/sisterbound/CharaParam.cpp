#include "scn/step/enemy/sisterbound/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 16;
    param._18 = 60;
    param._1c = 0.3f;
    param._20 = 2;
    param._24 = 1;
    return param;
}

}
}
}
}
}
