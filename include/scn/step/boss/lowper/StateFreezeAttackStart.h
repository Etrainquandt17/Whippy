#ifndef SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACKSTART_H
#define SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACKSTART_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFreezeAttackStart : public StateBase {
public:
    StateFreezeAttackStart(Boss* boss, u32 _2, u32 _3, u32 _4);
    virtual ~StateFreezeAttackStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    u32 _C;
    u32 _10;
    u32 mCount;
    hel::math::Vector3 mDir;
    f32 mSpeed;
};

}}}}  // namespace scn::step::boss::lowper

#endif
