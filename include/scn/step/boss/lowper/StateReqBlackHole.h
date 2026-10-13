#ifndef SCN_STEP_BOSS_LOWPER_STATEREQBLACKHOLE_H
#define SCN_STEP_BOSS_LOWPER_STATEREQBLACKHOLE_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateReqBlackHole : public StateBase {
public:
    StateReqBlackHole(Boss* boss, u32 kind);
    virtual ~StateReqBlackHole();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqHole();
    u32 mKind;
};

}}}}  // namespace scn::step::boss::lowper

#endif
