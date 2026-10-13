#ifndef SCN_STEP_BOSS_LANDIA_WAFTCTRL_H
#define SCN_STEP_BOSS_LANDIA_WAFTCTRL_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

}
class Boss;
namespace landia {

class WaftCtrl {
public:
    WaftCtrl(Boss& boss);
    void setWaveWidth(const hel::math::Vector2& width);
    void setWaveWidthZero();
    void setWaveThetaVel(const hel::math::Vector2& vel);
    void setWaveDefault();
    hel::math::Vector3 getRefPos() const;
    void setRefPos(const hel::math::Vector3& pos);
    void setPosEnf(const hel::math::Vector3& pos);
    void update();

private:
    Boss& mBoss;
    hel::math::Vector3 mRefPos;
    hel::math::Vector2 mTheta;
    hel::math::Vector2 mThetaVel;
    hel::math::Vector2 mWidth;
    hel::math::Vector2 mWidthTarget;
};

}
}
}
}

#endif
