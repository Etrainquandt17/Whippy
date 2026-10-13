#ifndef SCN_STEP_WEAPON_SLEEPSNOTBUBBLE_STATEMAIN_H
#define SCN_STEP_WEAPON_SLEEPSNOTBUBBLE_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace sleepsnotbubble {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual void procObjCollReact();
};

}}}}  // namespace scn::step::weapon::sleepsnotbubble

#endif
