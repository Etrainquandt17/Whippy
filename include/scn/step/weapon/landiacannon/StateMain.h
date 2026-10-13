#ifndef SCN_STEP_WEAPON_LANDIACANNON_STATEMAIN_H
#define SCN_STEP_WEAPON_LANDIACANNON_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiacannon {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void setInvisible();

private:
    u32 _8;
};

}}}}  // namespace scn::step::weapon::landiacannon

#endif
