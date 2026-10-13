#ifndef SCN_STEP_WEAPON_MAHOROAWARPHOLE_STATEEND_H
#define SCN_STEP_WEAPON_MAHOROAWARPHOLE_STATEEND_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole {

class StateEnd : public StateBase {
public:
    StateEnd(Weapon* weapon);
    virtual ~StateEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::weapon::mahoroawarphole

#endif
