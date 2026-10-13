#ifndef SCN_STEP_ENEMY_WHISPYAPPLE_WHISPYAPPLEUTILITY_H
#define SCN_STEP_ENEMY_WHISPYAPPLE_WHISPYAPPLEUTILITY_H

#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace whispyapple {

class WhispyAppleUtility {
public:
    static void ReqFallSE(Enemy& enemy);
    static void ReqBoundSE(Enemy& enemy);
    static void ReqBoundSEIfGordo(Enemy& enemy);
};

}
}
}
}

#endif
