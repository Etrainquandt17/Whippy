#ifndef SCN_STEP_ENEMY_OWGULF_STATEATTACK3WAY_H
#define SCN_STEP_ENEMY_OWGULF_STATEATTACK3WAY_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace owgulf {

class StateAttack3Way : public StateBase {
public:
    StateAttack3Way(Enemy* enemy);
    virtual void procAnim();

private:
    void shot(f32 angle);
    
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::owgulf

#endif
