#ifndef SCN_STEP_BOSS_LOWPER_STATEVORTEX_H
#define SCN_STEP_BOSS_LOWPER_STATEVORTEX_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateVortex : public StateBase {
public:
    StateVortex(Boss* boss);
    virtual ~StateVortex();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqBullet();
};

}}}}  // namespace scn::step::boss::lowper

#endif
