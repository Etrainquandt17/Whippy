#ifndef SCN_STEP_ENEMY_STARMAN_STATEJUMP_H
#define SCN_STEP_ENEMY_STARMAN_STATEJUMP_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace starman {

class StateJump : public StateBase {
public:
    StateJump(Enemy* enemy);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsEnd;
    f32 mSpeedH;
    bool mIsHighJump;
};

}}}}  // namespace scn::step::enemy::starman

#endif
