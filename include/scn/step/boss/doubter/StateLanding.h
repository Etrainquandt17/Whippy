#ifndef SCN_STEP_BOSS_DOUBTER_STATELANDING_H
#define SCN_STEP_BOSS_DOUBTER_STATELANDING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateLanding : public StateBase {
public:
    StateLanding(Boss* boss, u32 scriptKind = 2);
    virtual ~StateLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::doubter

#endif
