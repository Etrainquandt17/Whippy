#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_CAPTURECTRL_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_CAPTURECTRL_H

#include "hel/math/Vector3.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "scn/step/hero/CaptureHeroAttacker.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

}
class Boss;
namespace galactaknight {

class CaptureCtrl {
public:
    enum CaptureKind {
        CAPTURE_KIND_0,
        CAPTURE_KIND_1
    };

    CaptureCtrl(Boss& boss);

    void checkCapture();
    void reqStateFinish();
    void setConstraintPos(const hel::math::Vector3& pos);
    void clearCapture();
    void setCaptureKind(CaptureKind kind);

private:
    Boss& mBoss;
    mem::ExplicitAutoDeleteArray<hero::CaptureHeroAttacker, 4> mAttackers;
    CaptureKind mCaptureKind;
};

}}}}  // namespace scn::step::boss::galactaknight

#endif
