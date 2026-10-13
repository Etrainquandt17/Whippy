#ifndef SCN_STEP_WEAPON_ROAHOAR_STATEPURSUIT_H
#define SCN_STEP_WEAPON_ROAHOAR_STATEPURSUIT_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

class StatePursuit : public StateBase {
public:
    StatePursuit(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector3 mLeadPos;
    hel::math::Vector3 mSidePos;
    hel::math::Vector3 mPrevPos;
    hel::math::Vector3 mLeadDir;
    hel::math::Vector3 mSideDir;
    f32 mLeadSpeed;
    f32 mSideSpeed;
    f32 mRotV;
    f32 mSpin;
};

}}}}  // namespace scn::step::weapon::roahoar

#endif
