#ifndef SCN_STEP_ENEMY_GOLIATHICEBALL_STATEFOLLOW_H
#define SCN_STEP_ENEMY_GOLIATHICEBALL_STATEFOLLOW_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathiceball {

// TODO: stub
class StateFollow : public StateBase {
public:
    StateFollow(Enemy* enemy);
};

}
}
}
}

#endif
