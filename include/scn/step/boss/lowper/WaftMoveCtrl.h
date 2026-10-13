#ifndef SCN_STEP_BOSS_LOWPER_WAFTMOVECTRL_H
#define SCN_STEP_BOSS_LOWPER_WAFTMOVECTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}
class Boss;
namespace lowper {

class WaftMoveCtrl {
public:
    WaftMoveCtrl(Boss& boss);
    ~WaftMoveCtrl();
    void update();
    void setCenter(const hel::math::Vector3& center);
    void setIsValid(bool isValid);
    void setMoveIntpRate(f32 rate);
    void setWaveWidth(f32 width);
    hel::math::Vector3 getCenter() const;

private:
    Boss& mBoss;
    hel::math::Vector3 mCenter;
    f32 mPhaseX;
    f32 mPhaseY;
    f32 mMoveIntpRate;
    f32 mWaveWidth;
    f32 mWaveWidthTarget;
    bool mIsValid;
};

}}}}  // namespace scn::step::boss::lowper

#endif
