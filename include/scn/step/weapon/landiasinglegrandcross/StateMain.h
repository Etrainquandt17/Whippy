#ifndef SCN_STEP_WEAPON_LANDIASINGLEGRANDCROSS_STATEMAIN_H
#define SCN_STEP_WEAPON_LANDIASINGLEGRANDCROSS_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglegrandcross {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    bool mIsLoop;
};

}}}}  // namespace scn::step::weapon::landiasinglegrandcross

#endif
