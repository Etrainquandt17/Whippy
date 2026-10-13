#ifndef SCN_STEP_HERO_HAMMER_STATEWATERSPIN_H
#define SCN_STEP_HERO_HAMMER_STATEWATERSPIN_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class StateWaterSpin : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateWaterSpin(Hero* hero);
    virtual ~StateWaterSpin();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsBubble;
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::hammer

#endif
