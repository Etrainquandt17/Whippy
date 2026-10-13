#ifndef SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACK_H
#define SCN_STEP_BOSS_LOWPER_STATEFREEZEATTACK_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateFreezeAttack : public StateBase {
public:
    StateFreezeAttack(Boss* boss);
    virtual ~StateFreezeAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 mDir;
    u32 mCount;
};

}}}}  // namespace scn::step::boss::lowper

#endif
