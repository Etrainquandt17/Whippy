#ifndef SCN_STEP_ENEMY_FLAMER_STATEMOVE_H
#define SCN_STEP_ENEMY_FLAMER_STATEMOVE_H

#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

// TODO: members and the other functions.
class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
    virtual void procMove();
    virtual void procFixPos();
    virtual bool isInitCWR() const = 0;

    void setRot(bool isCWR);
};

class StateMoveCWR : public StateMove {
public:
    StateMoveCWR(Enemy* enemy) : StateMove(enemy) { setRot(true); }
    virtual bool isInitCWR() const { return true; }
};

class StateMoveCCW : public StateMove {
public:
    StateMoveCCW(Enemy* enemy) : StateMove(enemy) { setRot(false); }
    virtual bool isInitCWR() const { return false; }
};

}
}
}
}

#endif
