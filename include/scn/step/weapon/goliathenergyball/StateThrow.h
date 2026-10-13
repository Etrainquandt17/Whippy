#ifndef SCN_STEP_WEAPON_GOLIATHENERGYBALL_STATETHROW_H
#define SCN_STEP_WEAPON_GOLIATHENERGYBALL_STATETHROW_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

class StateThrow : public StateBase {
public:
    StateThrow(Weapon* weapon);
    virtual ~StateThrow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mLimitY;
    u32 mQuakeInterval;
};

}}}}  // namespace scn::step::weapon::goliathenergyball

#endif
