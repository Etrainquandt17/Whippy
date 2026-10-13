#ifndef SCN_STEP_ENEMY_MAHOROADEAD_STATEDEAD_H
#define SCN_STEP_ENEMY_MAHOROADEAD_STATEDEAD_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroadead {

// TODO: stub
class StateDead : public StateBase {
public:
    StateDead(Enemy* enemy);
};

}
}
}
}

#endif
