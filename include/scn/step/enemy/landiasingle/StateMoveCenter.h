#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEMOVECENTER_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEMOVECENTER_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateMoveCenter : public StateBase {
public:
    StateMoveCenter(Enemy* enemy);
    virtual ~StateMoveCenter();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector2 mStart;
    hel::math::Vector2 mEnd;
};

}
}
}
}

#endif
