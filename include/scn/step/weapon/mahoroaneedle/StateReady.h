#ifndef SCN_STEP_WEAPON_MAHOROANEEDLE_STATEREADY_H
#define SCN_STEP_WEAPON_MAHOROANEEDLE_STATEREADY_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

class StateReady : public StateBase {
public:
    StateReady(Weapon* weapon);
    virtual ~StateReady();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::weapon::mahoroaneedle

#endif
