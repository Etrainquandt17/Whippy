#ifndef SCN_STEP_HERO_HAMMER_STATEAIRSPIN_H
#define SCN_STEP_HERO_HAMMER_STATEAIRSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateAirSpin : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAirSpin(Hero* hero);
    virtual ~StateAirSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsEnd;
};

}}}}  // namespace scn::step::hero::hammer

#endif
