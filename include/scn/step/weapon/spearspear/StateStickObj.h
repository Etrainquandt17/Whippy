#ifndef SCN_STEP_WEAPON_SPEARSPEAR_STATESTICKOBJ_H
#define SCN_STEP_WEAPON_SPEARSPEAR_STATESTICKOBJ_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/StickObjAlgorithm.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace spearspear {

class StateStickObj : public StateBase {
public:
    StateStickObj(Weapon* weapon, f32 rot);
    virtual ~StateStickObj();
    virtual void procAnim();
    virtual void procMove();

private:
    StickObjAlgorithm mAlgorithm;
    u32 mFrame;
    f32 mRot;
};

}}}}  // namespace scn::step::weapon::spearspear

#endif
