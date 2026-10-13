#ifndef SCN_STEP_WEAPON_ROAHBULLET_STATEZMOVE_H
#define SCN_STEP_WEAPON_ROAHBULLET_STATEZMOVE_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

class StateZMove : public StateBase {
public:
    StateZMove(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mPassFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mTargetPos;
};

}}}}  // namespace scn::step::weapon::roahbullet

#endif
