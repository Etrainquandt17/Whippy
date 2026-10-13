#ifndef SCN_STEP_BOSS_DOUBTER_STATEPUNCH_H
#define SCN_STEP_BOSS_DOUBTER_STATEPUNCH_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/doubter/ScriptKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StatePunch : public StateBase {
public:
    StatePunch(Boss* boss, ScriptKind kind);
    virtual ~StatePunch();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mDecel;
};

}}}}  // namespace scn::step::boss::doubter

#endif
