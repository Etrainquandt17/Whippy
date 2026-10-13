#ifndef SCN_STEP_ENEMY_TSUKIKAGE_STATEWALL_H
#define SCN_STEP_ENEMY_TSUKIKAGE_STATEWALL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace tsukikage {

class StateWall : public StateBase {
public:
    StateWall(Enemy* enemy);
    virtual ~StateWall();
};

}
}
}
}

#endif
