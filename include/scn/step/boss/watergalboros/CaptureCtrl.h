#ifndef SCN_STEP_BOSS_WATERGALBOROS_CAPTURECTRL_H
#define SCN_STEP_BOSS_WATERGALBOROS_CAPTURECTRL_H

#include "scn/step/hero/CaptureHeroAttacker.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

}
class Boss;
namespace watergalboros {

class CaptureCtrl {
public:
    CaptureCtrl(Boss& boss);
    ~CaptureCtrl();

    void update();
    bool checkCapture();
    void setDamage(u32 damage);
    u32 getResistPower() const;
    void setInvisibility();
    void vomit();
    void vomitSoft();

private:
    Boss& mBoss;
    hero::CaptureHeroAttacker mAttacker;
};

}}}}  // namespace scn::step::boss::watergalboros

#endif
