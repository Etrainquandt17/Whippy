#ifndef SCN_STEP_WEAPON_ROAHBOOMERANG_STATEMAIN_H
#define SCN_STEP_WEAPON_ROAHBOOMERANG_STATEMAIN_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahboomerang {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mMoveFrame;
    u32 mEndFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector2 mRange;
    hel::math::Vector2 mRangeBack;
    u32 mHitInterval;
};

}}}}  // namespace scn::step::weapon::roahboomerang

#endif
