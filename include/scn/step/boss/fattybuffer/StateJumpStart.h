#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATEJUMPSTART_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATEJUMPSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateJumpStart : public StateBase {
public:
    StateJumpStart(Boss* boss, f32 speedH, f32 speedV);
    virtual ~StateJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeedH;
    f32 mSpeedV;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
