#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPHOLD_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPHOLD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStampHold : public StateBase {
public:
    StateStampHold(Boss* boss, bool isChase);
    virtual ~StateStampHold();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mStartY;
    bool mIsChase;
    f32 mSpeed;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
