#ifndef SCN_STEP_BOSS_GOLIATH_STATEBLIZZARDCHARGE_H
#define SCN_STEP_BOSS_GOLIATH_STATEBLIZZARDCHARGE_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/BlizzardDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateBlizzardCharge : public StateBase {
public:
    StateBlizzardCharge(Boss* boss, u32 frame, const BlizzardDesc& desc);
    virtual ~StateBlizzardCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    BlizzardDesc mDesc;
};

}}}}  // namespace scn::step::boss::goliath

#endif
