#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPLANDING_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESTAMPLANDING_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateStampLanding : public StateBase {
public:
    StateStampLanding(Boss* boss);
    virtual ~StateStampLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
