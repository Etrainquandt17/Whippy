#ifndef SCN_STEP_ENEMY_SHELD_STATECHASE_H
#define SCN_STEP_ENEMY_SHELD_STATECHASE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sheld {

class StateChase : public StateBase {
public:
    StateChase(Enemy* enemy);
    virtual ~StateChase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mAccel;
    f32 mAccelMax;
};

}}}}  // namespace scn::step::enemy::sheld

#endif
