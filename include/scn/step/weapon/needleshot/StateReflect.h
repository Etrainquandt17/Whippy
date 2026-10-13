#ifndef SCN_STEP_WEAPON_NEEDLESHOT_STATEREFLECT_H
#define SCN_STEP_WEAPON_NEEDLESHOT_STATEREFLECT_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

class StateReflect : public StateBase {
public:
    StateReflect(Weapon* weapon);
    virtual ~StateReflect();
    virtual void procAnim();
    virtual void procMove();

private:
    u32 mFrame;
    f32 mRot;
    f32 mRotSign;
};

}}}}  // namespace scn::step::weapon::needleshot

#endif
