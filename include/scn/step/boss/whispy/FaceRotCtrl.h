#ifndef SCN_STEP_BOSS_WHISPY_FACEROTCTRL_H
#define SCN_STEP_BOSS_WHISPY_FACEROTCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

}

class Boss;

namespace whispy {

class FaceRotCtrl {
public:
    FaceRotCtrl(Boss& boss);

    void setRotate(f32 rot);
    void reset();

private:
    Boss& mBoss;
};

}
}
}
}

#endif
