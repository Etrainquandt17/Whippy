#ifndef SCN_STEP_HERO_COMMON_STATESHIPREPAIRDEMOAFTER_H
#define SCN_STEP_HERO_COMMON_STATESHIPREPAIRDEMOAFTER_H

#include "hel/math/Vector3.h"
#include "scn/step/hero/StateBase.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateShipRepairDemoAfter : public StateBase {
public:
    StateShipRepairDemoAfter(Hero* hero);
    virtual ~StateShipRepairDemoAfter();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    util::FrameCounter mCounter;
    hel::math::Vector3 mPos;
};

}
}
}
}

#endif
