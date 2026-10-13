#include "scn/step/enemy/parasoldee/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasoldee {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._20 = 0;
    param._14 = 12;
    return param;
}

}
}
}
}
}
