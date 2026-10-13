#ifndef SCN_STEP_BOSS_DAMAGEINVINCIBLE_H
#define SCN_STEP_BOSS_DAMAGEINVINCIBLE_H

#include "types.h"

namespace scn {
namespace step {

namespace chara {

class DamageInfo;

}

namespace boss {

class Boss;

class DamageInvincible {
public:
    DamageInvincible(Boss& boss);

    void update();
    void setByDamage(const chara::DamageInfo& info);
    void cancel();
    bool isInvincible(const chara::DamageInfo& info) const;
    bool isInvincible() const;
    u32 getFrame() const;

private:
    Boss& mBoss;
    u32 mFrame;
};

}}}  // namespace scn::step::boss

#endif
