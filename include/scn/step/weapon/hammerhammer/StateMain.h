#ifndef SCN_STEP_WEAPON_HAMMERHAMMER_STATEMAIN_H
#define SCN_STEP_WEAPON_HAMMERHAMMER_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace hammerhammer {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void explode();

private:
    f32 _8;
    f32 _C;
};

}}}}  // namespace scn::step::weapon::hammerhammer

#endif
