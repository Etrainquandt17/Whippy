#ifndef SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEBIGJUMP_H
#define SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEBIGJUMP_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateFallIcicleBigJump : public StateBase {
public:
    StateFallIcicleBigJump(Boss* boss, u32 time);
    virtual ~StateFallIcicleBigJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mTime;
};

}}}}  // namespace scn::step::boss::goliath

#endif
