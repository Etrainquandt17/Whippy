#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPRISE_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPRISE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStampRise : public StateBase {
public:
    StateStampRise(Boss* boss, bool isChase);
    virtual ~StateStampRise();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mStartX;
    f32 mGoalX;
    bool mIsChase;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
