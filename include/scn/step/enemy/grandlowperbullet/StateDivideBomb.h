#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEDIVIDEBOMB_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_STATEDIVIDEBOMB_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace grandlowperbullet {

class StateDivideBomb : public StateBase {
public:
    StateDivideBomb(Enemy* enemy);
    virtual ~StateDivideBomb();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void reqBullet(f32 sign);

private:
    bool mIsLanded;
    f32 mFallAccel;
    u32 mFrame;
    u32 mShakeFrame;
};

}}}}  // namespace scn::step::enemy::grandlowperbullet

#endif
