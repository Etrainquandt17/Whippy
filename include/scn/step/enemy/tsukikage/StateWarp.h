#ifndef SCN_STEP_ENEMY_TSUKIKAGE_STATEWARP_H
#define SCN_STEP_ENEMY_TSUKIKAGE_STATEWARP_H

#include "scn/step/enemy/IState.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace tsukikage {

// TODO: members.
class StateWarp : public IState {
public:
    StateWarp(Enemy* enemy);
    virtual ~StateWarp();
};

}
}
}
}

#endif
