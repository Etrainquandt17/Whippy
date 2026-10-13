#ifndef SCN_STEP_WEAPON_GALACTASHOCKWAVE_STATEMAIN_H
#define SCN_STEP_WEAPON_GALACTASHOCKWAVE_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace galactashockwave {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void reqStar();

private:
    u32 _8;
    bool _C;
};

}}}}  // namespace scn::step::weapon::galactashockwave

#endif
