#ifndef SCN_STEP_ENEMY_SHELD_STATEESCAPE_H
#define SCN_STEP_ENEMY_SHELD_STATEESCAPE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sheld {

class StateEscape : public StateBase {
public:
    StateEscape(Enemy* enemy);
    virtual ~StateEscape();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
