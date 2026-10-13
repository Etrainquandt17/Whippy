#ifndef SCN_STEP_HERO_FIRE_STATEFIREBURNING_H
#define SCN_STEP_HERO_FIRE_STATEFIREBURNING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

// TODO: a stand-in until the unit is written.
class StateFireBurning : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, u32 count);

    StateFireBurning(Hero* hero);
};

}}}}  // namespace scn::step::hero::fire

#endif
