#ifndef SCN_STEP_ENEMY_SQUISHY_STATEMOVEINWATER_H
#define SCN_STEP_ENEMY_SQUISHY_STATEMOVEINWATER_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace squishy {

class StateMoveInWater : public StateBase {
public:
    StateMoveInWater(Enemy* enemy);
    virtual ~StateMoveInWater();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsInWater;
    u32 mFrame;
    u32 mMoveFrame;
};

}}}}  // namespace scn::step::enemy::squishy

#endif
