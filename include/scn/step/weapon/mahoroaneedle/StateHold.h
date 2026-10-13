#ifndef SCN_STEP_WEAPON_MAHOROANEEDLE_STATEHOLD_H
#define SCN_STEP_WEAPON_MAHOROANEEDLE_STATEHOLD_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

class StateHold : public StateBase {
public:
    StateHold(Weapon* weapon);
    virtual ~StateHold();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::weapon::mahoroaneedle

#endif
