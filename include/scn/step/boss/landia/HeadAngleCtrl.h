#ifndef SCN_STEP_BOSS_LANDIA_HEADANGLECTRL_H
#define SCN_STEP_BOSS_LANDIA_HEADANGLECTRL_H

#include "scn/step/boss/landia/NodeKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

}
class Boss;
namespace landia {

class HeadAngleCtrl {
public:
    HeadAngleCtrl(Boss& boss);
    void update();
    void toValid();
    void toInvalid();

private:
    void setMtx(NodeKind kind, f32 angle);

    Boss& mBoss;
    f32 mNeckAngle;
    f32 mHeadAngle;
    bool mIsValid;
};

}
}
}
}

#endif
