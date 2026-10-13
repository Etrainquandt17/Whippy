#ifndef SCN_STEP_ENEMY_SCARFY_STATECHASE_H
#define SCN_STEP_ENEMY_SCARFY_STATECHASE_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace scarfy {

class StateChase : public StateBase {
public:
    StateChase(Enemy* enemy);
    virtual ~StateChase();
    virtual void procAnim();
    virtual void procMove();

private:
    f32 getSpdLimit();
    f32 getSpd();
    
    u32 _8;
    f32 mSpd;
    f32 mSpdLimit;
    hel::math::Vector3 mVelocity;
};

}}}}  // namespace scn::step::enemy::scarfy

#endif
