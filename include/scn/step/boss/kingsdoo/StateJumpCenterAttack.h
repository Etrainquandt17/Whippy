#ifndef SCN_STEP_BOSS_KINGSDOO_STATEJUMPCENTERATTACK_H
#define SCN_STEP_BOSS_KINGSDOO_STATEJUMPCENTERATTACK_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

class StateJumpCenterAttack : public StateBase {
public:
    StateJumpCenterAttack(Boss* boss);
    virtual ~StateJumpCenterAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsJump;
    bool mIsFall;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mCenter;
};

}}}}  // namespace scn::step::boss::kingsdoo

#endif
