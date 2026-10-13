#ifndef SCN_STEP_WEAPON_MAHOROASUPERFIRE_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROASUPERFIRE_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperfire {

// TODO: members; the unit is not written yet (procAnim, procMove and procFixPos are its overrides, no destructor).
class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::weapon::mahoroasuperfire

#endif
