#ifndef SCN_STEP_BOSS_LOWPER_STATEBOMBFAR_H
#define SCN_STEP_BOSS_LOWPER_STATEBOMBFAR_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateBombFar : public StateBase {
public:
    StateBombFar(Boss* boss);
    virtual ~StateBombFar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqBomb(f32 speedX);
    hel::math::Vector3 mPos;
    u32 mCount;
    bool mIsStarted;
};

}}}}  // namespace scn::step::boss::lowper

#endif
