#ifndef SCN_STEP_WEAPON_HRD3EYELASER_STATEEND_H
#define SCN_STEP_WEAPON_HRD3EYELASER_STATEEND_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace hrd3eyelaser {

class StateEnd : public StateBase {
public:
    StateEnd(Weapon* weapon, u32 frame);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFrame;
    f32 mTotalFrame;
};

}}}}  // namespace scn::step::weapon::hrd3eyelaser

#endif
