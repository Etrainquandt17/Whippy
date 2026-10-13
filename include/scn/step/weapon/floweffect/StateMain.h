#ifndef SCN_STEP_WEAPON_FLOWEFFECT_STATEMAIN_H
#define SCN_STEP_WEAPON_FLOWEFFECT_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace floweffect {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();
};

}}}}  // namespace scn::step::weapon::floweffect

#endif
