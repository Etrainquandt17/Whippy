#ifndef SCN_STEP_WEAPON_LANDIASTAR_STATEMAIN_H
#define SCN_STEP_WEAPON_LANDIASTAR_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/landiastar/Variation.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiastar {

// TODO: members and overrides; the unit is not written yet.
class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon, Variation variation);
};

}}}}  // namespace scn::step::weapon::landiastar

#endif
