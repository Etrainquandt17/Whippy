#ifndef SCN_STEP_BOSS_COMMON_STATELANDING_H
#define SCN_STEP_BOSS_COMMON_STATELANDING_H

#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

namespace common {

class StateLanding : public StateBase {
public:
    StateLanding(Boss* boss);
    StateLanding(Boss* boss, int scriptKind);
    virtual ~StateLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void init();
};

}}}}  // namespace scn::step::boss::common

#endif
