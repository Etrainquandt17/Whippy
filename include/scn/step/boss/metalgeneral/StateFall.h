#ifndef SCN_STEP_BOSS_METALGENERAL_STATEFALL_H
#define SCN_STEP_BOSS_METALGENERAL_STATEFALL_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateFall : public StateBase {
public:
    StateFall(Boss* boss);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
