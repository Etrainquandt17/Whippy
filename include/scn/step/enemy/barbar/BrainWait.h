#ifndef SCN_STEP_ENEMY_BARBAR_BRAINWAIT_H
#define SCN_STEP_ENEMY_BARBAR_BRAINWAIT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

class BrainWait : public BrainBase {
public:
    BrainWait(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
