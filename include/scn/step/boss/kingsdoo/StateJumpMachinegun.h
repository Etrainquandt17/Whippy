#ifndef SCN_STEP_BOSS_KINGSDOO_STATEJUMPMACHINEGUN_H
#define SCN_STEP_BOSS_KINGSDOO_STATEJUMPMACHINEGUN_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/kingsdoo/StateJumpMachinegunStart.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

class StateJumpMachinegun : public StateBase {
public:
    StateJumpMachinegun(Boss* boss);
    virtual ~StateJumpMachinegun();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqMachinegun();

    u32 mCount;
    hel::math::Vector2 mStartPos;
    f32 mRotV;
    bool mIsSwing;
};

}}}}  // namespace scn::step::boss::kingsdoo

#endif
