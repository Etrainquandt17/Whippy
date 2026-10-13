#ifndef SCN_STEP_ENEMY_GOLIATHICICLE_STATEFLOORHIT_H
#define SCN_STEP_ENEMY_GOLIATHICICLE_STATEFLOORHIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace goliathicicle {

class StateFloorHit : public StateBase {
public:
    StateFloorHit(Enemy* enemy);
    virtual ~StateFloorHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mEndFrame;
    u32 mShakeFrame;
};

}}}}  // namespace scn::step::enemy::goliathicicle

#endif
