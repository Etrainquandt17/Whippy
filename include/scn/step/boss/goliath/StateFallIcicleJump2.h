#ifndef SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEJUMP2_H
#define SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEJUMP2_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateFallIcicleJump2 : public StateBase {
public:
    StateFallIcicleJump2(Boss* boss, u32 time, u32 _2);
    virtual ~StateFallIcicleJump2();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mTime;
    u32 _10;
};

}}}}  // namespace scn::step::boss::goliath

#endif
