#ifndef SCN_STEP_HERO_WING_STATEDASHATTACKWALLHIT_H
#define SCN_STEP_HERO_WING_STATEDASHATTACKWALLHIT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace wing {

class StateDashAttackWallHit : public StateBase {
public:
    StateDashAttackWallHit(Hero* hero);
    virtual ~StateDashAttackWallHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::wing

#endif
