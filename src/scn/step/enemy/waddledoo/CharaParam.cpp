#include "scn/step/enemy/waddledoo/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 7;
    param._14 = 18;
    param._3c = 19;
    return param;
}

}
}
}
}
}
