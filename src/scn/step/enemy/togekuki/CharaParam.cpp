#include "scn/step/enemy/togekuki/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._24 = 2;
    param._14 = 52;
    param._45 = true;
    param._47 = false;
    param._10 = 6;
    return param;
}

}
}
}
}
}
