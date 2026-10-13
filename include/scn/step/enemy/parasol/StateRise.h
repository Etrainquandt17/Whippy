#ifndef SCN_STEP_ENEMY_PARASOL_STATERISE_H
#define SCN_STEP_ENEMY_PARASOL_STATERISE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace parasol {

class StateRise : public StateBase {
public:
    StateRise(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeedV;
    f32 mRot;
};

}}}}  // namespace scn::step::enemy::parasol

#endif
