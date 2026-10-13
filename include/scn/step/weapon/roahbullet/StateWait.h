#ifndef SCN_STEP_WEAPON_ROAHBULLET_STATEWAIT_H
#define SCN_STEP_WEAPON_ROAHBULLET_STATEWAIT_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

class StateWait : public StateBase {
public:
    StateWait(Weapon* weapon);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mWaitFrame;
    f32 mRot;
};

}}}}  // namespace scn::step::weapon::roahbullet

#endif
