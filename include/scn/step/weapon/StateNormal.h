#ifndef SCN_STEP_WEAPON_STATENORMAL_H
#define SCN_STEP_WEAPON_STATENORMAL_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {

class StateNormal : public StateBase {
public:
    StateNormal(Weapon* weapon);
    virtual ~StateNormal();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}  // namespace scn::step::weapon

#endif
