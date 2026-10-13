#ifndef SCN_STEP_BOSS_COMMON_STATEMOVEBACK_H
#define SCN_STEP_BOSS_COMMON_STATEMOVEBACK_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/common/StateMoveDesc.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

class StateMoveBack : public StateBase {
public:
    StateMoveBack(Boss* boss, StateMoveDesc desc, unsigned long scriptKind);
    virtual ~StateMoveBack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    StateMoveDesc mDesc;
};

}}}}  // namespace scn::step::boss::common

#endif
