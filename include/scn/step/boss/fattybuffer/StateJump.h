#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEJUMP_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEJUMP_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateJump : public StateBase {
public:
    StateJump(Boss* boss, f32 speedH, f32 speedV);
    virtual ~StateJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
