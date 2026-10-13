#ifndef SCN_STEP_WEAPON_ROAHSTAR_STATESHOT_H
#define SCN_STEP_WEAPON_ROAHSTAR_STATESHOT_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahstar {

class StateShot : public StateBase {
public:
    StateShot(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}}}}  // namespace scn::step::weapon::roahstar

#endif
