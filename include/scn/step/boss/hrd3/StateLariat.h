#ifndef SCN_STEP_BOSS_HRD3_STATELARIAT_H
#define SCN_STEP_BOSS_HRD3_STATELARIAT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

class StateLariat : public StateBase {
public:
    StateLariat(Boss* boss, u32 frame, f32 distance);
    virtual ~StateLariat();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void updateRotate();

    u32 mCount;
    u32 mFrame;
    f32 mSpeedMax;
    f32 mSpeed;
    f32 mAccel;
    f32 mDecel;
    f32 mRot;
    f32 mRotSpeed;
    bool mIsMove;
};

}}}}  // namespace scn::step::boss::hrd3

#endif
