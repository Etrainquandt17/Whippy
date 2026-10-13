#ifndef SCN_STEP_WEAPON_FATTYBUFFERWATERCANNON_STATEMAIN_H
#define SCN_STEP_WEAPON_FATTYBUFFERWATERCANNON_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace fattybufferwatercannon {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
};

}}}}  // namespace scn::step::weapon::fattybufferwatercannon

#endif
