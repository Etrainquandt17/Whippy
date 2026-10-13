#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLSTART_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLSTART_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellStart : public StateBase {
public:
    StateSwellStart(Boss* boss);
    virtual ~StateSwellStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
