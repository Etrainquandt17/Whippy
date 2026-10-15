#ifndef SCN_STEP_BOSS_GOLIATH_STATEPUNCH_H
#define SCN_STEP_BOSS_GOLIATH_STATEPUNCH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StatePunch : public StateBase {
public:
    StatePunch(Boss* boss, f32 elevX, bool isContinue);
    virtual ~StatePunch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mAttackFrame;
    bool mIsContinue;
};

}}}}  // namespace scn::step::boss::goliath

#endif
