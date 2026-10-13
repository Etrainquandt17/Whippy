#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEANGER_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEANGER_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateAnger : public StateBase {
public:
    StateAnger(Boss* boss);
    virtual ~StateAnger();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mScale;
    bool mIsScaling;
    u32 mCount;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
