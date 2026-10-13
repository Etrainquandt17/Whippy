#ifndef SCN_STEP_WEAPON_ROAHBULLET_STATEAPPEAR_H
#define SCN_STEP_WEAPON_ROAHBULLET_STATEAPPEAR_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

class StateAppear : public StateBase {
public:
    StateAppear(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mWaitFrame;
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mEndPos;
};

}}}}  // namespace scn::step::weapon::roahbullet

#endif
