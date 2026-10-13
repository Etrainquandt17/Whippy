#ifndef SCN_STEP_WEAPON_HRD3EYELASER_STATEMAIN_H
#define SCN_STEP_WEAPON_HRD3EYELASER_STATEMAIN_H

#include "scn/step/boss/Boss.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {
namespace hrd3eyelaser {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    util::ObjRefHandle<boss::Boss> mBoss;
    f32 mLength;
    f32 _1C;
    bool mIsHit;
};

}}}}  // namespace scn::step::weapon::hrd3eyelaser

#endif
