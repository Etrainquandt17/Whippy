#ifndef SCN_STEP_ENEMY_WAPODPOD_STATEWAIT_H
#define SCN_STEP_ENEMY_WAPODPOD_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace wapodpod {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual ~StateWait();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
