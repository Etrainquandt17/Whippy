#ifndef SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEENERGYBALLSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateEnergyBallStart : public StateBase {
public:
    StateEnergyBallStart(Boss* boss, u32 _1, u32 _2, f32 _3);
    virtual ~StateEnergyBallStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    u32 _C;
    f32 _10;
};

}}}}  // namespace scn::step::boss::goliath

#endif
