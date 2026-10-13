#ifndef SCN_STEP_BOSS_DOUBTER_STATECATCH_H
#define SCN_STEP_BOSS_DOUBTER_STATECATCH_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateCatch : public StateBase {
public:
    StateCatch(Boss* boss);
    virtual ~StateCatch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    f32 mDecel;
};

}}}}  // namespace scn::step::boss::doubter

#endif
