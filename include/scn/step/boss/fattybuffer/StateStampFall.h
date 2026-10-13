#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPFALL_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPFALL_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStampFall : public StateBase {
public:
    StateStampFall(Boss* boss);
    virtual ~StateStampFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mStartY;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
