#ifndef SCN_STEP_BOSS_FATTYBUFFER_CANNONCAPTURECTRL_H
#define SCN_STEP_BOSS_FATTYBUFFER_CANNONCAPTURECTRL_H

#include "hel/math/Vector3.h"
#include "mem/ExplicitAutoDeleteArray.h"
#include "scn/step/hero/CaptureHeroAttacker.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

}
class Boss;
namespace fattybuffer {

class CannonCaptureCtrl {
public:
    CannonCaptureCtrl(Boss& boss);
    ~CannonCaptureCtrl();
    void checkCapture();
    void reqStateRelease();
    void clearCapture();
    void setConstraintPos(const hel::math::Vector3& pos);
    bool isCapture() const;

private:
    Boss& mBoss;
    mem::ExplicitAutoDeleteArray<hero::CaptureHeroAttacker, 4> mAttackers;
};

}
}
}
}

#endif
