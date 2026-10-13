#ifndef SCN_STEP_BOSS_LANDIA_HOWLCTRL_H
#define SCN_STEP_BOSS_LANDIA_HOWLCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

}
class Boss;
namespace landia {

class HowlCtrl {
public:
    HowlCtrl(Boss& boss);
    void update();
    void reqStop();

private:
    Boss& mBoss;
    u32 mCount;
    bool mIsStop;
};

}
}
}
}

#endif
