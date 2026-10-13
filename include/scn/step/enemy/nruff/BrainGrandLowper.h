#ifndef SCN_STEP_ENEMY_NRUFF_BRAINGRANDLOWPER_H
#define SCN_STEP_ENEMY_NRUFF_BRAINGRANDLOWPER_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

class BrainGrandLowper : public BrainBase {
public:
    BrainGrandLowper(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual bool onLanding();
};

}
}
}
}

#endif
