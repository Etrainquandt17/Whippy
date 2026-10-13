#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTALACTITEJUMP_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTALACTITEJUMP_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/fattybuffer/StalactiteJumpKind.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStalactiteJump : public StateBase {
public:
    StateStalactiteJump(Boss* boss, StalactiteJumpKind kind);
    virtual ~StateStalactiteJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StalactiteJumpKind mKind;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
