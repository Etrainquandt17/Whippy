#ifndef SCN_STEP_BOSS_WHISPY_STATECHEWING_H
#define SCN_STEP_BOSS_WHISPY_STATECHEWING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateChewing : public StateBase {
public:
    StateChewing(Boss* boss);
    virtual ~StateChewing();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    bool mIsFirst;
};

}}}}  // namespace scn::step::boss::whispy

#endif
