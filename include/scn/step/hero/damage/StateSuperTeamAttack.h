#ifndef SCN_STEP_HERO_DAMAGE_STATESUPERTEAMATTACK_H
#define SCN_STEP_HERO_DAMAGE_STATESUPERTEAMATTACK_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateSuperTeamAttack : public StateBase {
public:
    StateSuperTeamAttack(Hero* hero);
    virtual ~StateSuperTeamAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::damage

#endif
