#ifndef SCN_STEP_BOSS_FATTYBUFFER_EYECTRL_H
#define SCN_STEP_BOSS_FATTYBUFFER_EYECTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

}
class Boss;
namespace fattybuffer {

class EyeCtrl {
public:
    EyeCtrl(Boss& boss);
    void update();

private:
    Boss& mBoss;
};

}
}
}
}

#endif
