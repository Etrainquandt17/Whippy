#ifndef SCN_STEP_HERO_MIKE_STATECHARGE_H
#define SCN_STEP_HERO_MIKE_STATECHARGE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace mike {

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
    bool isStandMike();
    bool isShakeMax();

    bool mIsCharged;
};

}}}}  // namespace scn::step::hero::mike

#endif
