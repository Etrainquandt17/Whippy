#ifndef SCN_STEP_HERO_HIGHJUMP_STATECHARGE_H
#define SCN_STEP_HERO_HIGHJUMP_STATECHARGE_H

#include "scn/step/hero/StateBase.h"
#include "scn/step/hero/highjump/JumpKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class StateCharge : public StateBase {
public:
    static bool tryToChangeState(Hero* hero);

    StateCharge(Hero* hero);
    virtual ~StateCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    JumpKind mKind;
};

}}}}  // namespace scn::step::hero::highjump

#endif
