#ifndef SCN_STEP_WEAPON_MAHOROALASER_STATEHIDE_H
#define SCN_STEP_WEAPON_MAHOROALASER_STATEHIDE_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroalaser {

class StateHide : public StateBase {
public:
    StateHide(Weapon* weapon);
    virtual ~StateHide();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::weapon::mahoroalaser

#endif
