#ifndef SCN_STEP_BOSS_GOLIATH_PUNCHCTRL_H
#define SCN_STEP_BOSS_GOLIATH_PUNCHCTRL_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}
class Boss;
namespace goliath {

class PunchCtrl {
public:
    PunchCtrl(Boss& boss);

    void update();
    void setLength(f32 length);
    void resetLength();
    void registGenerateStarHeight(f32 height);
    void unregistGenerateStarHeight();
    hel::math::Vector2 getGenerateStarSpeedV(f32 height) const;

private:
    Boss& mBoss;
    f32 mLength;
    f32 mTargetLength;
    f32 mGenerateStarHeight;
    bool mIsGenerateStarHeightRegistered;
};

}}}}  // namespace scn::step::boss::goliath

#endif
