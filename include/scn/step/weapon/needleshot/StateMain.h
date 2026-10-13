#ifndef SCN_STEP_WEAPON_NEEDLESHOT_STATEMAIN_H
#define SCN_STEP_WEAPON_NEEDLESHOT_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    void dead();
    bool isHitMap();
    void updateMapColl();

    bool mIsDead;
    f32 mRot;
};

}}}}  // namespace scn::step::weapon::needleshot

#endif
