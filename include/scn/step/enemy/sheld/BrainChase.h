#ifndef SCN_STEP_ENEMY_SHELD_BRAINCHASE_H
#define SCN_STEP_ENEMY_SHELD_BRAINCHASE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

class BrainChase : public BrainBase {
public:
    BrainChase(Enemy& enemy);
    virtual bool onLanding();
};

}
}
}
}

#endif
