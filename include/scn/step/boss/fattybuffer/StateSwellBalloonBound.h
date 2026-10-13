#ifndef SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBALLOONBOUND_H
#define SCN_STEP_BOSS_FATTYBUFFER_STATESWELLBALLOONBOUND_H

#include "hel/math/Vector3.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class StateSwellBalloonBound : public StateBase {
public:
    enum Kind {
        KIND_ROOF,
        KIND_WALL,
        KIND_FLOOR,
    };

    StateSwellBalloonBound(Boss* boss, Kind kind, u32 count);
    virtual ~StateSwellBalloonBound();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Kind mKind;
    u32 mCount;
    hel::math::Vector3 mVelocity;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
