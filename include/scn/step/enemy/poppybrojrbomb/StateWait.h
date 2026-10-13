#ifndef SCN_STEP_ENEMY_POPPYBROJRBOMB_STATEWAIT_H
#define SCN_STEP_ENEMY_POPPYBROJRBOMB_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace poppybrojrbomb {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual ~StateWait();
};

}
}
}
}

#endif
