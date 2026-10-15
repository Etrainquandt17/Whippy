#ifndef SCN_STEP_BOSS_GOLIATH_STATESWOOPSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATESWOOPSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateSwoopStart : public StateBase {
public:
    StateSwoopStart(Boss* boss, u32 _1, u32 _2);
    virtual ~StateSwoopStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    u32 _C;
};

}}}}  // namespace scn::step::boss::goliath

#endif
