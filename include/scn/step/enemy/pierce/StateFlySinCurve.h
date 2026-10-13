#ifndef SCN_STEP_ENEMY_PIERCE_STATEFLYSINCURVE_H
#define SCN_STEP_ENEMY_PIERCE_STATEFLYSINCURVE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pierce {

class StateFlySinCurve : public StateBase {
public:
    StateFlySinCurve(Enemy* enemy);
    virtual ~StateFlySinCurve();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mAngle;
    f32 mSpeedH;
    bool mIsAttack;
    bool mIsAttackEnd;
};

}}}}  // namespace scn::step::enemy::pierce

#endif
