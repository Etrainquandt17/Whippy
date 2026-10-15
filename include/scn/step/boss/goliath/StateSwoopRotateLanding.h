#ifndef SCN_STEP_BOSS_GOLIATH_STATESWOOPROTATELANDING_H
#define SCN_STEP_BOSS_GOLIATH_STATESWOOPROTATELANDING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateSwoopRotateLanding : public StateBase {
public:
    StateSwoopRotateLanding(Boss* boss);
    virtual ~StateSwoopRotateLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void updateRotate();
    void generateIceBall(f32 offsetX, f32 speedX);
    u32 mRotState;
    f32 mRot;
    f32 mRotSpeed;
};

}}}}  // namespace scn::step::boss::goliath

#endif
