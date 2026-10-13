#ifndef SCN_STEP_ENEMY_OWGULF_BRAINFLYWAIT_H
#define SCN_STEP_ENEMY_OWGULF_BRAINFLYWAIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

class BrainFlyWait : public BrainBase {
public:
    BrainFlyWait(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
