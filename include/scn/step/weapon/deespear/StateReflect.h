#ifndef SCN_STEP_WEAPON_DEESPEAR_STATEREFLECT_H
#define SCN_STEP_WEAPON_DEESPEAR_STATEREFLECT_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

class StateReflect : public StateBase {
public:
    StateReflect(Weapon* weapon);
    virtual ~StateReflect();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    f32 mRot;
};

}}}}  // namespace scn::step::weapon::deespear

#endif
