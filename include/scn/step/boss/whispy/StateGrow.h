#ifndef SCN_STEP_BOSS_WHISPY_STATEGROW_H
#define SCN_STEP_BOSS_WHISPY_STATEGROW_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

class StateGrow : public StateBase {
public:
    StateGrow(Boss* boss);
    virtual ~StateGrow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
};

}}}}  // namespace scn::step::boss::whispy

#endif
