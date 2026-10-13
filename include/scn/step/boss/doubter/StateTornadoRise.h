#ifndef SCN_STEP_BOSS_DOUBTER_STATETORNADORISE_H
#define SCN_STEP_BOSS_DOUBTER_STATETORNADORISE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateTornadoRise : public StateBase {
public:
    StateTornadoRise(Boss* boss);
    virtual ~StateTornadoRise();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    f32 mStartY;
};

}}}}  // namespace scn::step::boss::doubter

#endif
