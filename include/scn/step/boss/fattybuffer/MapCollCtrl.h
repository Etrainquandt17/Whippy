#ifndef SCN_STEP_BOSS_FATTYBUFFER_MAPCOLLCTRL_H
#define SCN_STEP_BOSS_FATTYBUFFER_MAPCOLLCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

}
class Boss;
namespace fattybuffer {

class MapCollCtrl {
public:
    MapCollCtrl(Boss& boss);
    void setDefault();
    void setBalloon();

private:
    Boss& mBoss;
};

}
}
}
}

#endif
