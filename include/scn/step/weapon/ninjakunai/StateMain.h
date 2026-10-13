#ifndef SCN_STEP_WEAPON_NINJAKUNAI_STATEMAIN_H
#define SCN_STEP_WEAPON_NINJAKUNAI_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procConstraint();
    virtual void procObjCollReact();
};

}}}}  // namespace scn::step::weapon::ninjakunai

#endif
