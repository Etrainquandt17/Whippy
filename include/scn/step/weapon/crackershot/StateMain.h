#ifndef SCN_STEP_WEAPON_CRACKERSHOT_STATEMAIN_H
#define SCN_STEP_WEAPON_CRACKERSHOT_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace crackershot {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void mfExplode();

private:
    u32 _8;
    bool _C;
    u32 _10;
    u32 _14;
    f32 _18;
};

}}}}  // namespace scn::step::weapon::crackershot

#endif
