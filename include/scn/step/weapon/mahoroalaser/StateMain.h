#ifndef SCN_STEP_WEAPON_MAHOROALASER_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROALASER_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroalaser {

// TODO: the members are the ones seen in use so far; the unit is not written yet.
class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 _8;
    u32 _C;
    u32 _10;
    u32 _14;
    f32 _18;
    f32 _1C;
    bool _20;
};

}}}}  // namespace scn::step::weapon::mahoroalaser

#endif
