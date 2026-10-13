#ifndef SCN_STEP_BOSS_WATERGALBOROS_STATECAPTURE_H
#define SCN_STEP_BOSS_WATERGALBOROS_STATECAPTURE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

class StateCapture : public StateBase {
public:
    StateCapture(Boss* boss);
    virtual ~StateCapture();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    bool mIsFirst;
};

}}}}  // namespace scn::step::boss::watergalboros

#endif
