#ifndef SCN_STEP_BOSS_FATTYBUFFER_POSTURECTRL_H
#define SCN_STEP_BOSS_FATTYBUFFER_POSTURECTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

}
class Boss;
namespace fattybuffer {

class PostureCtrl {
public:
    PostureCtrl(Boss& boss);
    void update();
    void resetTarget();
    void setTargetRoof();
    f32 getUpSign() const;

private:
    Boss& mBoss;
    f32 mAngle;
    f32 mTargetAngle;
    f32 mRate;
};

}}}}  // namespace scn::step::boss::fattybuffer

#endif
