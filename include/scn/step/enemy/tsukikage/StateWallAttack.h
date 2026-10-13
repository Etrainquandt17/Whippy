#ifndef SCN_STEP_ENEMY_TSUKIKAGE_STATEWALLATTACK_H
#define SCN_STEP_ENEMY_TSUKIKAGE_STATEWALLATTACK_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace tsukikage {

class StateWallAttack : public StateBase {
public:
    StateWallAttack(Enemy* enemy);
    virtual ~StateWallAttack();
    virtual void procAnim();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::enemy::tsukikage

#endif
