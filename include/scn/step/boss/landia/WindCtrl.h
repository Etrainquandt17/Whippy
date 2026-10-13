#ifndef SCN_STEP_BOSS_LANDIA_WINDCTRL_H
#define SCN_STEP_BOSS_LANDIA_WINDCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

}
class Boss;
namespace landia {

class WindCtrl {
public:
    WindCtrl(Boss& boss);
    ~WindCtrl();
    void update();
    void set(f32 speed, f32 accel, f32 speedMax);
    void clear();

private:
    Boss& mBoss;
    u32 mAreaIds[7];
    f32 mSpeed;
    f32 mAccel;
    f32 mSpeedMax;
};

}}}}  // namespace scn::step::boss::landia

#endif
