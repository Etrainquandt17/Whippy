#ifndef SCN_STEP_BOSS_METALGENERAL_STATECIRCLINGFLIGHT_H
#define SCN_STEP_BOSS_METALGENERAL_STATECIRCLINGFLIGHT_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateCirclingFlight : public StateBase {
public:
    StateCirclingFlight(Boss* boss);
    virtual ~StateCirclingFlight();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mDir;
    f32 mRot;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
