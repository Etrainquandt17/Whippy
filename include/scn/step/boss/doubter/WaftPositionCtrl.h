#ifndef SCN_STEP_BOSS_DOUBTER_WAFTPOSITIONCTRL_H
#define SCN_STEP_BOSS_DOUBTER_WAFTPOSITIONCTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

}
class Boss;
namespace doubter {

class WaftPositionCtrl {
public:
    WaftPositionCtrl(Boss& boss);
    ~WaftPositionCtrl();
    void update();
    hel::math::Vector3 getNextPos() const;

private:
    Boss& mBoss;
    f32 mTheta;
};

}
}
}
}

#endif
