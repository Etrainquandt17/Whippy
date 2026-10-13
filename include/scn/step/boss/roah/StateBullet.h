#ifndef SCN_STEP_BOSS_ROAH_STATEBULLET_H
#define SCN_STEP_BOSS_ROAH_STATEBULLET_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

class StateBullet : public StateBase {
public:
    struct Config {
        int _0;
        int _4;
    };

    StateBullet(Boss* boss, Config config);
    virtual ~StateBullet();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mCount;
    hel::math::Vector2 mBasePos;
    bool mIsMove;
    bool mIsRequest;
    Config mConfig;
};

}}}}  // namespace scn::step::boss::roah

#endif
