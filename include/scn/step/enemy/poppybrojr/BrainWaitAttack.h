#ifndef SCN_STEP_ENEMY_POPPYBROJR_BRAINWAITATTACK_H
#define SCN_STEP_ENEMY_POPPYBROJR_BRAINWAITATTACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace poppybrojr {

class BrainWaitAttack : public BrainBase {
public:
    BrainWaitAttack(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
