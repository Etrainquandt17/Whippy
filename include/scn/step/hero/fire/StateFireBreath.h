#ifndef SCN_STEP_HERO_FIRE_STATEFIREBREATH_H
#define SCN_STEP_HERO_FIRE_STATEFIREBREATH_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

// TODO: a stand-in until the unit is written.
class StateFireBreath : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateFireBreath(Hero* hero);
};

}}}}  // namespace scn::step::hero::fire

#endif
