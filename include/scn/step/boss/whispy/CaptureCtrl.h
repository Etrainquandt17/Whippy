#ifndef SCN_STEP_BOSS_WHISPY_CAPTURECTRL_H
#define SCN_STEP_BOSS_WHISPY_CAPTURECTRL_H

#include "scn/step/hero/CaptureHeroAttacker.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

}

class Boss;

namespace whispy {

class CaptureCtrl {
public:
    CaptureCtrl(Boss& boss);

    bool checkCapture();
    void vomit();
    void vomitSoft();
    void release();
    void setDamage(u32 damage);
    u32 getResistPower() const;

private:
    Boss& mBoss;
    hero::CaptureHeroAttacker mAttacker;
};

}}}}  // namespace scn::step::boss::whispy

#endif
