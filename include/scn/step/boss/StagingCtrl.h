#ifndef SCN_STEP_BOSS_STAGINGCTRL_H
#define SCN_STEP_BOSS_STAGINGCTRL_H

#include "types.h"

namespace hel {
namespace math {

class Vector2;

}
}

namespace scn {
namespace step {
namespace boss {

class Boss;

class StagingCtrl {
public:
    StagingCtrl(Boss& boss);
    ~StagingCtrl();

    void initZoom(const hel::math::Vector2& pos, f32 zoom);
    void setZoom(const hel::math::Vector2& pos, f32 zoom);
    void setZoom(f32 zoom);
    void unsetZoom();
    void changeZoomIntpRate(f32 rate);

private:
    Boss& mBoss;
    u32 mZoomID;
};

}
}
}

#endif
