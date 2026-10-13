#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBACKJUMPSTART_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBACKJUMPSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellBackJumpStart : public StateBase {
public:
    StateSwellBackJumpStart(Boss* boss, f32 speedH, f32 speedV);
    virtual ~StateSwellBackJumpStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mSpeedH;
    f32 mSpeedV;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
