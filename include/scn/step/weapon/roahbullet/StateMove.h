#ifndef SCN_STEP_WEAPON_ROAHBULLET_STATEMOVE_H
#define SCN_STEP_WEAPON_ROAHBULLET_STATEMOVE_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

class StateMove : public StateBase {
public:
    StateMove(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector3 mDir;
};

}}}}  // namespace scn::step::weapon::roahbullet

#endif
