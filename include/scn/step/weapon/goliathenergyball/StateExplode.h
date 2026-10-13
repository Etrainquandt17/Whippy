#ifndef SCN_STEP_WEAPON_GOLIATHENERGYBALL_STATEEXPLODE_H
#define SCN_STEP_WEAPON_GOLIATHENERGYBALL_STATEEXPLODE_H

#include "scn/step/hero/CaptureHeroAttacker.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

class StateExplode : public StateBase {
public:
    StateExplode(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void reqEffect();
    void reqStar();

private:
    u32 mFrame;
    bool mIsEffectRequested;
    hero::CaptureHeroAttacker mAttacker;
};

}}}}  // namespace scn::step::weapon::goliathenergyball

#endif
