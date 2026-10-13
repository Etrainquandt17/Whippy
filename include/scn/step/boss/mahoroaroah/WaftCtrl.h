#ifndef SCN_STEP_BOSS_MAHOROAROAH_WAFTCTRL_H
#define SCN_STEP_BOSS_MAHOROAROAH_WAFTCTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

}
class Boss;
namespace mahoroaroah {

class WaftCtrl {
public:
    WaftCtrl(Boss& boss);
    ~WaftCtrl();

    hel::math::Vector3 getRefPos() const;
    void setRefPos(const hel::math::Vector3& pos);
    void update();
    void setToValid();

private:
    Boss& mBoss;
    hel::math::Vector3 mRefPos;
    hel::math::Vector3 mTheta;
    hel::math::Vector3 mThetaVel;
    bool mIsValid;
};

}}}}  // namespace scn::step::boss::mahoroaroah

#endif
