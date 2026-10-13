#ifndef SCN_STEP_BOSS_HRD3_CAMERACTRL_H
#define SCN_STEP_BOSS_HRD3_CAMERACTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

}
class Boss;
namespace hrd3 {

class CameraCtrl {
public:
    CameraCtrl(Boss& boss);

    void update();
    void setMain();
    void setZoomOut();

private:
    Boss& mBoss;
    u32 mCount;
};

}
}
}
}

#endif
