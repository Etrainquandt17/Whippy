#ifndef SCN_STEP_WEAPON_MAHOROANEEDLE_STATESTART_H
#define SCN_STEP_WEAPON_MAHOROANEEDLE_STATESTART_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

class StateStart : public StateBase {
public:
    StateStart(Weapon* weapon);
    virtual ~StateStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void updateAttack();
};

}}}}  // namespace scn::step::weapon::mahoroaneedle

#endif
