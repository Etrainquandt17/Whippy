#ifndef SCN_STEP_HERO_CAPTUREHERORECEIVER_H
#define SCN_STEP_HERO_CAPTUREHERORECEIVER_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class CaptureHeroReceiver {
public:
    bool isCapture() const;
    void setCanCapture(bool canCapture);
    void resetResistPower();
    void enableResist(bool flag);
    void disableResist(bool flag);
    void setSuccess();
    hel::math::Vector3 getConstraintPos() const;
    hel::math::Vector3 getAttackerPos() const;
    u32 getResistPower() const;
};

}
}
}

#endif
