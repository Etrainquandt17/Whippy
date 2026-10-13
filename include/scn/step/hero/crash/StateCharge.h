#ifndef SCN_STEP_HERO_CRASH_STATECHARGE_H
#define SCN_STEP_HERO_CRASH_STATECHARGE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace crash {

class StateCharge : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCharge(Hero* hero);
    virtual ~StateCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void chkCharge();
    void changeMotion();
    bool isShakeMax();

    bool mIsCharged;
    bool mIsAttack;
};

}}}}  // namespace scn::step::hero::crash

#endif
