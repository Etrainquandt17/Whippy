#ifndef SCN_STEP_WEAPON_MAHOROAFROZENAREA_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROAFROZENAREA_STATEMAIN_H

#include "scn/step/chara/Lifetime.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroafrozenarea {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    chara::Lifetime mLifetime;
    u32 mAreaId;
};

}}}}  // namespace scn::step::weapon::mahoroafrozenarea

#endif
