#ifndef SCN_STEP_ENEMY_WHIPPY_STATEATTACK_H
#define SCN_STEP_ENEMY_WHIPPY_STATEATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace whippy {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual ~StateAttack();
    virtual void procAnim();
    virtual void procFixPos();

private:
    void aimAntenna(f32 angle);
    
    u32 mFrame;
    f32 mAngle;
};

}}}}  // namespace scn::step::enemy::whippy

#endif
