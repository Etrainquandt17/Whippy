#include "scn/step/enemy/poppybrojrbomb/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojrbomb {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._45 = true;
    param._30 = 413;
    param._10 = 15;
    param._47 = false;
    param._4b = true;
    return param;
}

}
}
}
}
}
