#ifndef SCN_STEP_WEAPON_MAHOROABLACKHOLEBG_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROABLACKHOLEBG_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackholebg {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::weapon::mahoroablackholebg

#endif
