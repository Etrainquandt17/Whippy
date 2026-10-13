#ifndef SCN_STEP_WEAPON_MAHOROAICICLE_STATEFLOORHIT_H
#define SCN_STEP_WEAPON_MAHOROAICICLE_STATEFLOORHIT_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaicicle {

class StateFloorHit : public StateBase {
public:
    StateFloorHit(Weapon* weapon);
    virtual ~StateFloorHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mWait;
};

}}}}  // namespace scn::step::weapon::mahoroaicicle

#endif
