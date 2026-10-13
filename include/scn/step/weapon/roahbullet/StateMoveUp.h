#ifndef SCN_STEP_WEAPON_ROAHBULLET_STATEMOVEUP_H
#define SCN_STEP_WEAPON_ROAHBULLET_STATEMOVEUP_H

#include "hel/math/Vector2.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

class StateMoveUp : public StateBase {
public:
    StateMoveUp(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector2 mStartPos;
    hel::math::Vector2 mEndPos;
};

}}}}  // namespace scn::step::weapon::roahbullet

#endif
