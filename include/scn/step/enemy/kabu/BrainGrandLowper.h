#ifndef SCN_STEP_ENEMY_KABU_BRAINGRANDLOWPER_H
#define SCN_STEP_ENEMY_KABU_BRAINGRANDLOWPER_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

class BrainGrandLowper : public BrainBase {
public:
    BrainGrandLowper(Enemy& enemy);
    virtual bool onStart();
    virtual void update();
};

}
}
}
}

#endif
