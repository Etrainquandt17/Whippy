#ifndef SCN_STEP_ENEMY_SEARCHES_STATEMOVE_H
#define SCN_STEP_ENEMY_SEARCHES_STATEMOVE_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace searches {

class StateMove : public StateBase {
public:
    StateMove(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mDir;
    u32 mFrame;
    bool mIsWait;
};

}}}}  // namespace scn::step::enemy::searches

#endif
