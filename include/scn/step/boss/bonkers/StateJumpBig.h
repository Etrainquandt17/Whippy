#ifndef SCN_STEP_BOSS_BONKERS_STATEJUMPBIG_H
#define SCN_STEP_BOSS_BONKERS_STATEJUMPBIG_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

class StateJumpBig : public StateBase {
public:
    StateJumpBig(Boss* boss);
    virtual ~StateJumpBig();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mStartPos;
    f32 mDistance;
};

}}}}  // namespace scn::step::boss::bonkers

#endif
