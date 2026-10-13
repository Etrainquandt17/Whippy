#ifndef SCN_STEP_WEAPON_MAHOROABLACKHOLE_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROABLACKHOLE_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackhole {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool _8;
    f32 mFrameRate;
    u32 mWait;
};

}}}}  // namespace scn::step::weapon::mahoroablackhole

#endif
