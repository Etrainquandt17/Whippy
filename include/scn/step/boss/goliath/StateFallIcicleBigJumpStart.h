#ifndef SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEBIGJUMPSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEBIGJUMPSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateFallIcicleBigJumpStart : public StateBase {
public:
    StateFallIcicleBigJumpStart(Boss* boss, u32 _1);
    virtual ~StateFallIcicleBigJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}}}}  // namespace scn::step::boss::goliath

#endif
