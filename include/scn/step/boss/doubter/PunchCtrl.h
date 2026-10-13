#ifndef SCN_STEP_BOSS_DOUBTER_PUNCHCTRL_H
#define SCN_STEP_BOSS_DOUBTER_PUNCHCTRL_H

#include "g3d/NodeAccessor.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/doubter/NodeKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

}
class Boss;
namespace doubter {

class PunchCtrl {
public:
    PunchCtrl(Boss& boss, NodeKind node, f32 sign);
    void update();
    void start(f32 speed, u32 frame);
    void catchSearchStart();
    void catchSearchEnd();
    void catchEnd();
    void deadEnd();
    bool isValid() const;
    bool isPunch() const;
    hel::math::Vector3 getPos() const;

private:
    void updateFrame();
    void updateSRT();
    void updateEffect();
    void reqFire(bool flag);
    void reqStar();
    void setHandSubAnim();
    void clearHandSubAnim();

    Boss& mBoss;
    g3d::NodeAccessor mNode;
    u32 mState;
    u32 mCount;
    u32 mFrame;
    f32 _24;
    f32 _28;
    hel::math::Vector3 _2C;
    hel::math::Vector3 _38;
    f32 _44;
    bool _48;
    f32 mSign;
    bool _50;
    bool _51;
};

}
}
}
}

#endif
