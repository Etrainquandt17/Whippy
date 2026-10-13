#ifndef SCN_STEP_BOSS_METALGENERAL_STATEBOMB_H
#define SCN_STEP_BOSS_METALGENERAL_STATEBOMB_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class StateBomb : public StateBase {
public:
    struct Config {
        Config(f32 speedX, f32 speedY, bool isBig) : mSpeed(speedX, speedY), mIsBig(isBig) {}

        hel::math::Vector2 mSpeed;
        bool mIsBig;
    };

    StateBomb(Boss* boss, Config config);
    virtual ~StateBomb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    Config mConfig;
};

}}}}  // namespace scn::step::boss::metalgeneral

#endif
