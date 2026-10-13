#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {
namespace ParamBase {

CharaParam Create() {
    CharaParam param = {};
    param._0 = 1.0f;
    hel::math::Vec2 v = { 0.0f, 0.5f };
    param._4.x = v.x;
    param._4.y = v.y;
    param._c = 50.0f;
    param._10 = 0;
    param._14 = 16;
    param._18 = 15;
    param._1c = 1.0f;
    param._20 = 1;
    param._24 = 0;
    param._28 = 0;
    param._2c = 0.5f;
    param._30 = 407;
    param._34 = 1.0f;
    param._38 = 0;
    param._3c = 2;
    param._40 = 1;
    param._44 = false;
    param._45 = false;
    param._46 = true;
    param._47 = true;
    param._48 = true;
    param._49 = false;
    param._4a = true;
    param._4b = false;
    param._4c = true;
    param._4d = false;
    return param;
}

}
}
}
}
}
