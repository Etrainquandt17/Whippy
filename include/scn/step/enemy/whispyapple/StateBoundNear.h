#ifndef SCN_STEP_ENEMY_WHISPYAPPLE_STATEBOUNDNEAR_H
#define SCN_STEP_ENEMY_WHISPYAPPLE_STATEBOUNDNEAR_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace whispyapple {

class StateBoundNear : public StateBase {
public:
    StateBoundNear(Enemy* enemy, bool flag);
    virtual ~StateBoundNear();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    f32 mRotX;
    f32 mFloorY;
    f32 mSpeedV;
};

}}}}  // namespace scn::step::enemy::whispyapple

#endif
