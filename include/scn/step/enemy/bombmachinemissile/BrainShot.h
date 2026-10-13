#ifndef SCN_STEP_ENEMY_BOMBMACHINEMISSILE_BRAINSHOT_H
#define SCN_STEP_ENEMY_BOMBMACHINEMISSILE_BRAINSHOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bombmachinemissile {

class BrainShot : public BrainBase {
public:
    BrainShot(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
