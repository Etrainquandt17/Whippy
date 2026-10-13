#ifndef SCN_STEP_WEAPON_SWORDBEAM_STATEMAIN_H
#define SCN_STEP_WEAPON_SWORDBEAM_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace swordbeam {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::weapon::swordbeam

#endif
