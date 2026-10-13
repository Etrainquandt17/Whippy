#ifndef SCN_STEP_BOSS_METALGENERAL_STATENEEDLE_H
#define SCN_STEP_BOSS_METALGENERAL_STATENEEDLE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateNeedle : public StateBase {
public:
    StateNeedle(Boss* boss, u32 index);
    virtual ~StateNeedle();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
