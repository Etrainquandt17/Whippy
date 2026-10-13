#ifndef SCN_STEP_WEAPON_GOLIATHENERGYBALL_STATEMAIN_H
#define SCN_STEP_WEAPON_GOLIATHENERGYBALL_STATEMAIN_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mStartPos;
    u32 mFrame;
};

}}}}  // namespace scn::step::weapon::goliathenergyball

#endif
