#ifndef SCN_STEP_BOSS_DOUBTER_STATETORNADOSEARCH_H
#define SCN_STEP_BOSS_DOUBTER_STATETORNADOSEARCH_H

#include "gobj/MoveParam.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateTornadoSearch : public StateBase {
public:
    StateTornadoSearch(Boss* boss, u32 frame, f32 rate);
    virtual ~StateTornadoSearch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mCount;
    gobj::MoveParamAccel mAccel;
};

}}}}  // namespace scn::step::boss::doubter

#endif
