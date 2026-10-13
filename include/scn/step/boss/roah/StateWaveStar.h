#ifndef SCN_STEP_BOSS_ROAH_STATEWAVESTAR_H
#define SCN_STEP_BOSS_ROAH_STATEWAVESTAR_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateWaveStar : public StateBase {
public:
    struct Config {
        u32 _0;
    };

    StateWaveStar(Boss* boss, Config config);
    virtual ~StateWaveStar();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mBasePos;
    Config mConfig;
};

}}}}  // namespace scn::step::boss::roah

#endif
