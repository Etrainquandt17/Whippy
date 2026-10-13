#ifndef SCN_STEP_BOSS_METALGENERAL_STATEBIT_H
#define SCN_STEP_BOSS_METALGENERAL_STATEBIT_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateBit : public StateBase {
public:
    StateBit(Boss* boss, u32 num);
    virtual ~StateBit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mNum;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
