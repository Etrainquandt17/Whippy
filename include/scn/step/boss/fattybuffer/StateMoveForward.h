#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEMOVEFORWARD_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEMOVEFORWARD_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateMoveForward : public StateBase {
public:
    StateMoveForward(Boss* boss, f32 rate);
    virtual ~StateMoveForward();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRate;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
