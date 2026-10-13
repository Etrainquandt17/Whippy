#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBACKJUMPLANDING_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBACKJUMPLANDING_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellBackJumpLanding : public StateBase {
public:
    StateSwellBackJumpLanding(Boss* boss);
    virtual ~StateSwellBackJumpLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
