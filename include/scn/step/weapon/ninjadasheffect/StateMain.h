#ifndef SCN_STEP_WEAPON_NINJADASHEFFECT_STATEMAIN_H
#define SCN_STEP_WEAPON_NINJADASHEFFECT_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjadasheffect {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    int mWait;
    int mFrame;
    bool mIsEnd;
};

}}}}  // namespace scn::step::weapon::ninjadasheffect

#endif
