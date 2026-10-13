#ifndef SCN_STEP_ENEMY_BULBY_STATEATTACK_H
#define SCN_STEP_ENEMY_BULBY_STATEATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace bulby {

class StateAttack : public StateBase {
public:
    StateAttack(Enemy* enemy);
    virtual void procAnim();
    virtual void procFixPos();

private:
    void shot(hel::math::Vector3 velocity);
    
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::bulby

#endif
