#ifndef SCN_STEP_BOSS_DOUBTER_CAPTURECTRL_H
#define SCN_STEP_BOSS_DOUBTER_CAPTURECTRL_H

#include "mem/ExplicitAutoDeleteArray.h"
#include "scn/step/hero/CaptureHeroAttacker.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

}
class Boss;
namespace doubter {

class CaptureCtrl {
public:
    // TODO: the names of the states.
    enum State {
        STATE_0,
        STATE_HOLD,
        STATE_HIDE,
        STATE_JUGGLING,
        STATE_SHOT_PREPARE,
    };

    CaptureCtrl(Boss& boss);
    void update();
    void checkRelease();
    bool checkCapture();
    bool isCapture() const;
    bool isCaptureJuggling() const;
    u32 getCaptureNum() const;
    void clearCapture();
    void juggling();
    void shotPrepare();
    void shot();
    void release();
    void setDamage(u32 damage);
    void hide();
    void setIsRightDir();

private:
    void updateConstraintPosAtHold();
    void updateConstraintPosAtHide();
    void updateConstraintPosAtJuggling();
    void updateConstraintPosAtShotprepare();

    Boss& mBoss;
    mem::ExplicitAutoDeleteArray<hero::CaptureHeroAttacker, 3> mAttackers;
    State mState;
    u32 mDamageIndex;
};

}}}}  // namespace scn::step::boss::doubter

#endif
