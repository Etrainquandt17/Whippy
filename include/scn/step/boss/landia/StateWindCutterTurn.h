#ifndef SCN_STEP_BOSS_LANDIA_STATEWINDCUTTERTURN_H
#define SCN_STEP_BOSS_LANDIA_STATEWINDCUTTERTURN_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

class StateWindCutterTurn : public StateBase {
public:
    StateWindCutterTurn(Boss* boss);
    virtual ~StateWindCutterTurn();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    u32 mTurnCount;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mGoalPos;
};

}}}}  // namespace scn::step::boss::landia

#endif
