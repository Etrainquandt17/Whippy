#ifndef SCN_STEP_BOSS_BARRIERINVINCIBLE_H
#define SCN_STEP_BOSS_BARRIERINVINCIBLE_H

namespace scn {
namespace step {

namespace chara {

class DamageInfo;

}

namespace boss {

class Boss;

class BarrierInvincible {
public:
    BarrierInvincible(Boss& boss);

    bool isInvincible(const chara::DamageInfo& info) const;
    void setIsValid(bool isValid);

private:
    Boss& mBoss;
    bool mIsValid;
};

}}}  // namespace scn::step::boss

#endif
