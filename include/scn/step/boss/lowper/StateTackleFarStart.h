#ifndef SCN_STEP_BOSS_LOWPER_STATETACKLEFARSTART_H
#define SCN_STEP_BOSS_LOWPER_STATETACKLEFARSTART_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateTackleFarStart : public StateBase {
public:
    StateTackleFarStart(Boss* boss);
    virtual ~StateTackleFarStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector3 _8;
    u32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
};

}}}}  // namespace scn::step::boss::lowper

#endif
