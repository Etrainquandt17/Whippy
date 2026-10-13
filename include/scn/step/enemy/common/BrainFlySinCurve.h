#ifndef SCN_STEP_ENEMY_COMMON_BRAINFLYSINCURVE_H
#define SCN_STEP_ENEMY_COMMON_BRAINFLYSINCURVE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainFlySinCurve : public BrainBase {
public:
    BrainFlySinCurve(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
};

}
}
}
}

#endif
