#include "scn/step/enemy/parasoldoo/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldoo {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 0;
    param._20 = 0;
    param._14 = 18;
    return param;
}

}
}
}
}
}
