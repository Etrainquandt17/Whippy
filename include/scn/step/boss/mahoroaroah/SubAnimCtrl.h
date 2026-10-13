#ifndef SCN_STEP_BOSS_MAHOROAROAH_SUBANIMCTRL_H
#define SCN_STEP_BOSS_MAHOROAROAH_SUBANIMCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

}
class Boss;
namespace mahoroaroah {

class SubAnimCtrl {
public:
    SubAnimCtrl(Boss& boss);

    void setup();
    void update();
    bool chkValidAnim();

private:
    Boss& mBoss;
    bool mIsValid;
};

}
}
}
}

#endif
