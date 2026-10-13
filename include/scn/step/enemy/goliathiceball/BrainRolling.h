#ifndef SCN_STEP_ENEMY_GOLIATHICEBALL_BRAINROLLING_H
#define SCN_STEP_ENEMY_GOLIATHICEBALL_BRAINROLLING_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {

class BrainRolling : public BrainBase {
public:
    BrainRolling(Enemy& enemy);
    virtual bool onStart();
    virtual bool onLanding();
};

}
}
}
}

#endif
