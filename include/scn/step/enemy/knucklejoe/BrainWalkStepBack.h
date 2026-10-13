#ifndef SCN_STEP_ENEMY_KNUCKLEJOE_BRAINWALKSTEPBACK_H
#define SCN_STEP_ENEMY_KNUCKLEJOE_BRAINWALKSTEPBACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

class BrainWalkStepBack : public BrainBase {
public:
    BrainWalkStepBack(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
    virtual void update();
};

}
}
}
}

#endif
