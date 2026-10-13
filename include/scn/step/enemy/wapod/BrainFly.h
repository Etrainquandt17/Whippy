#ifndef SCN_STEP_ENEMY_WAPOD_BRAINFLY_H
#define SCN_STEP_ENEMY_WAPOD_BRAINFLY_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

class BrainFly : public BrainBase {
public:
    BrainFly(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
