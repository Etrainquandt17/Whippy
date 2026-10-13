#ifndef SCN_STEP_WEAPON_ROAHOAR_STATESPREAD_H
#define SCN_STEP_WEAPON_ROAHOAR_STATESPREAD_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

class StateSpread : public StateBase {
public:
    StateSpread(Weapon* weapon);
    virtual ~StateSpread();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    hel::math::Vector3 mEndPos;
};

}}}}  // namespace scn::step::weapon::roahoar

#endif
