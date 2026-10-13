#ifndef SCN_STEP_BOSS_LOWPER_STATEWARPIN_H
#define SCN_STEP_BOSS_LOWPER_STATEWARPIN_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateWarpIn : public StateBase {
public:
    StateWarpIn(Boss* boss);
    virtual ~StateWarpIn();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}}}}  // namespace scn::step::boss::lowper

#endif
