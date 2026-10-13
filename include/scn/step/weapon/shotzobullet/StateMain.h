#ifndef SCN_STEP_WEAPON_SHOTZOBULLET_STATEMAIN_H
#define SCN_STEP_WEAPON_SHOTZOBULLET_STATEMAIN_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace shotzobullet {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procObjCollReact();

private:
    hel::math::Vector3 mVelocity;
    f32 mRot;
    u32 mFrame;
};

}}}}  // namespace scn::step::weapon::shotzobullet

#endif
