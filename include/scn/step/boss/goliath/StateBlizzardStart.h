#ifndef SCN_STEP_BOSS_GOLIATH_STATEBLIZZARDSTART_H
#define SCN_STEP_BOSS_GOLIATH_STATEBLIZZARDSTART_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/BlizzardDesc.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateBlizzardStart : public StateBase {
public:
    StateBlizzardStart(Boss* boss, u32 frame, const BlizzardDesc& desc);
    virtual ~StateBlizzardStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    BlizzardDesc mDesc;
};

}}}}  // namespace scn::step::boss::goliath

#endif
