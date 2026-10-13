#ifndef SCN_STEP_HERO_BOMB_STATESWING_H
#define SCN_STEP_HERO_BOMB_STATESWING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

class GearBombController;

class StateSwing : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, GearBombController& controller);

    StateSwing(Hero* hero, GearBombController& controller);
    virtual ~StateSwing();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    GearBombController& mController;
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::bomb

#endif
