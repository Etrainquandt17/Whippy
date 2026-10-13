#ifndef SCN_STEP_ENEMY_SCARFY_STATEESCAPE_H
#define SCN_STEP_ENEMY_SCARFY_STATEESCAPE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace scarfy {

class StateEscape : public StateBase {
public:
    StateEscape(Enemy* enemy);
    virtual void procMove();

private:
    f32 getSpdLimit();
    f32 getSpd();
};

}
}
}
}

#endif
