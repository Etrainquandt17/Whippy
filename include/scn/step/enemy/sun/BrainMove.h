#ifndef SCN_STEP_ENEMY_SUN_BRAINMOVE_H
#define SCN_STEP_ENEMY_SUN_BRAINMOVE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sun {

class BrainMove : public BrainBase {
public:
    BrainMove(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
