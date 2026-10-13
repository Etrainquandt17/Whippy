#ifndef SCN_STEP_CHARA_BODYCOLL_H
#define SCN_STEP_CHARA_BODYCOLL_H

#include "ocoll/Hit.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/ocoll/Flag.h"
#include "scn/step/ocoll/HitResistLv.h"
#include "scn/step/ocoll/TeamFlag.h"

namespace scn {
namespace step {
namespace chara {

class DamageInfo;

// TODO: members and the other functions.
class BodyColl {
public:
    ~BodyColl();

    void clear();
    void setStateNormal();
    void setStateInvincible();
    void setStateXlu();
    void setStateHitOnly();
    void setStateCaptureOnly();
    void initAttackType(ocoll::AttackType type);
    void setFlagXlu(ocoll::Flag flag);
    void setTeamXlu(ocoll::TeamFlag flag);
    void changeAttackType(ocoll::AttackType type);
    void resetAttackType();
    void setAttackTypeOver(ocoll::AttackType type);
    void unsetAttackTypeOver();
    void setResistLv(ocoll::HitResistLv lv);
    ocoll::HitResistLv getResistLv();
    void setPauseAttack(bool isPause);
    bool isCollide() const;
    bool isHitValid() const;
    ::ocoll::Hit& hit() { return mHit; }
    DamageInfo damageInfo() const;

private:
    u32 _0[2];
    ::ocoll::Hit mHit;
};

}}}  // namespace scn::step::chara

#endif
