#ifndef SCN_STEP_WEAPON_MAHOROASUPERBEAMBALL_STATEGLIDE_H
#define SCN_STEP_WEAPON_MAHOROASUPERBEAMBALL_STATEGLIDE_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroasuperbeamball {

class StateGlide : public StateBase {
public:
    StateGlide(Weapon* weapon, const hel::math::Vector3& targetPos, u32 totalFrame);
    virtual ~StateGlide();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mTargetPos;
    u32 mTotalFrame;
    u32 mFrame;
    u32 mShakeInterval;
    u32 mQuakeInterval;
    bool mIsAttack;
};

}}}}  // namespace scn::step::weapon::mahoroasuperbeamball

#endif
