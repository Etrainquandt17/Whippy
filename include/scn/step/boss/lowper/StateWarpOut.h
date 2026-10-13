#ifndef SCN_STEP_BOSS_LOWPER_STATEWARPOUT_H
#define SCN_STEP_BOSS_LOWPER_STATEWARPOUT_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateWarpOut : public StateBase {
public:
    StateWarpOut(Boss* boss, const hel::math::Vector3& pos);
    virtual ~StateWarpOut();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}}}}  // namespace scn::step::boss::lowper

#endif
