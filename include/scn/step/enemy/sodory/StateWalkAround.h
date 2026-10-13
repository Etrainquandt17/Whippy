#ifndef SCN_STEP_ENEMY_SODORY_STATEWALKAROUND_H
#define SCN_STEP_ENEMY_SODORY_STATEWALKAROUND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sodory {

class StateWalkAround : public StateBase {
public:
    StateWalkAround(Enemy* enemy);
    virtual ~StateWalkAround();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsTurning;
    bool mIsRightDir;
};

}
}
}
}

#endif
