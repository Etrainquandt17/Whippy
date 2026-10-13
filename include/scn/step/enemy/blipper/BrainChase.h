#ifndef SCN_STEP_ENEMY_BLIPPER_BRAINCHASE_H
#define SCN_STEP_ENEMY_BLIPPER_BRAINCHASE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

class BrainChase : public BrainBase {
public:
    BrainChase(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
