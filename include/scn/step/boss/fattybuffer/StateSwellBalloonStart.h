#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBALLOONSTART_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBALLOONSTART_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellBalloonStart : public StateBase {
public:
    StateSwellBalloonStart(Boss* boss, const hel::math::Vector3& speed, u32 count);
    virtual ~StateSwellBalloonStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mSpeed;
    u32 mCount;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
