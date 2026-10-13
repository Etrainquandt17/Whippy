#ifndef SCN_STEP_ENEMY_TSUKIKAGE_STATEJUMPATTACK_H
#define SCN_STEP_ENEMY_TSUKIKAGE_STATEJUMPATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace tsukikage {

class StateJumpAttack : public StateBase {
public:
    StateJumpAttack(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mAttackFrame;
    bool mIsAttack;
    bool mIsFall;
    bool mIsAttackEnd;
};

}}}}  // namespace scn::step::enemy::tsukikage

#endif
