#ifndef SCN_STEP_HERO_DAMAGE_STATEABILITYCRASH_H
#define SCN_STEP_HERO_DAMAGE_STATEABILITYCRASH_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateAbilityCrash : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAbilityCrash(Hero* hero);
    virtual ~StateAbilityCrash();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::damage

#endif
