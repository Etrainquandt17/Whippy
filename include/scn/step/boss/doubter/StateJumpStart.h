#ifndef SCN_STEP_BOSS_DOUBTER_STATEJUMPSTART_H
#define SCN_STEP_BOSS_DOUBTER_STATEJUMPSTART_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateJumpStart : public StateBase {
public:
    StateJumpStart(Boss* boss, const hel::math::Vector2& speed, u32 count);
    virtual ~StateJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector2 mSpeed;
    u32 mCount;
};

}}}}  // namespace scn::step::boss::doubter

#endif
