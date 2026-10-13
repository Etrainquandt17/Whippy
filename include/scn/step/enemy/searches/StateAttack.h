#ifndef SCN_STEP_ENEMY_SEARCHES_STATEATTACK_H
#define SCN_STEP_ENEMY_SEARCHES_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace searches {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual void procAnim();

private:
    u32 mFrame;
    int mDeadFrame;
    bool mIsExploded;
};

}}}}  // namespace scn::step::enemy::searches

#endif
