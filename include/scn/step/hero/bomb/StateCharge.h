#ifndef SCN_STEP_HERO_BOMB_STATECHARGE_H
#define SCN_STEP_HERO_BOMB_STATECHARGE_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

class GearBombController;

// TODO: a stand-in until the unit is written.
class StateCharge : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, GearBombController& controller);

    StateCharge(Hero* hero, GearBombController& controller, bool isUp);
};

}}}}  // namespace scn::step::hero::bomb

#endif
