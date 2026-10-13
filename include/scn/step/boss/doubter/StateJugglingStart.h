#ifndef SCN_STEP_BOSS_DOUBTER_STATEJUGGLINGSTART_H
#define SCN_STEP_BOSS_DOUBTER_STATEJUGGLINGSTART_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateJugglingStart : public StateBase {
public:
    StateJugglingStart(Boss* boss);
    virtual ~StateJugglingStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 _8;
    u32 mCount;
    bool mIsCapture;
};

}}}}  // namespace scn::step::boss::doubter

#endif
