#ifndef SCN_STEP_WEAPON_SPEARSPEAR_STATESTICKWALL_H
#define SCN_STEP_WEAPON_SPEARSPEAR_STATESTICKWALL_H

#include "scn/step/weapon/StateBase.h"
#include "scn/step/weapon/StickWallAlgorithm.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace spearspear {

class StateStickWall : public StateBase {
public:
    StateStickWall(Weapon* weapon, f32 rot);
    virtual ~StateStickWall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    StickWallAlgorithm mAlgorithm;
    u32 mFrame;
    f32 mRot;
};

}}}}  // namespace scn::step::weapon::spearspear

#endif
