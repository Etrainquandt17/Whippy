#ifndef SCN_STEP_ENEMY_WADDLEDOO_BRAINWALKAROUND_H
#define SCN_STEP_ENEMY_WADDLEDOO_BRAINWALKAROUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

class BrainWalkAround : public BrainBase {
public:
    BrainWalkAround(Enemy& enemy);
    virtual bool onLanding();
    virtual void update();
};

}
}
}
}

#endif
