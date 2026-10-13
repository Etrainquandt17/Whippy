#ifndef SCN_STEP_WEAPON_MAHOROAHAMMERSHOCKWAVE_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROAHAMMERSHOCKWAVE_STATEMAIN_H

#include "scn/step/chara/Lifetime.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroahammershockwave {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    chara::Lifetime mLifetime;
    f32 mPrevPosX;
};

}}}}  // namespace scn::step::weapon::mahoroahammershockwave

#endif
