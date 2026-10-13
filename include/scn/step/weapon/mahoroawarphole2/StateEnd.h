#ifndef SCN_STEP_WEAPON_MAHOROAWARPHOLE2_STATEEND_H
#define SCN_STEP_WEAPON_MAHOROAWARPHOLE2_STATEEND_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole2 {

class StateEnd : public StateBase {
public:
    StateEnd(Weapon* weapon);
    virtual ~StateEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::weapon::mahoroawarphole2

#endif
