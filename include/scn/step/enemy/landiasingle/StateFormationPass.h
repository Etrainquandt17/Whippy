#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEFORMATIONPASS_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEFORMATIONPASS_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

// TODO: stub
class StateFormationPass : public StateBase {
public:
    struct Config {
        u8 _0;
        u8 _1;
    };

    StateFormationPass(Enemy* enemy, Config config);
};

}
}
}
}

#endif
