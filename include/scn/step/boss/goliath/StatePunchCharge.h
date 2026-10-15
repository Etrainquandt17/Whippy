#ifndef SCN_STEP_BOSS_GOLIATH_STATEPUNCHCHARGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEPUNCHCHARGE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StatePunchCharge : public StateBase {
public:
    StatePunchCharge(Boss* boss, u32 _1, u32 _2, bool _3);
    virtual ~StatePunchCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    u32 _C;
    bool _10;
};

}}}}  // namespace scn::step::boss::goliath

#endif
