#ifndef SCN_STEP_ENEMY_STARMAN_STATEFLY_H
#define SCN_STEP_ENEMY_STARMAN_STATEFLY_H

#include "gobj/MoveParam.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace starman {

class StateFly : public StateBase {
public:
    StateFly(Enemy* enemy);
    virtual ~StateFly();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void flySinCurve();
    void flyStraight();
    
    gobj::MoveParamAccel mAccel;
    f32 mAngle;
    bool mIsStraight;
    u32 mFrame;
    f32 mPrevX;
    f32 mCurX;
    f32 mRise;
};

}}}}  // namespace scn::step::enemy::starman

#endif
