#ifndef SCN_STEP_ENEMY_WADDLEDOO_BRAINWALKSTRAIGHT_H
#define SCN_STEP_ENEMY_WADDLEDOO_BRAINWALKSTRAIGHT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

class BrainWalkStraight : public BrainBase {
public:
    BrainWalkStraight(Enemy& enemy);
    virtual bool onLanding();
    virtual void update();
};

}
}
}
}

#endif
