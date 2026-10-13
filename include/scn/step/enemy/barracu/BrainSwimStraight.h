#ifndef SCN_STEP_ENEMY_BARRACU_BRAINSWIMSTRAIGHT_H
#define SCN_STEP_ENEMY_BARRACU_BRAINSWIMSTRAIGHT_H

#include "scn/step/enemy/BrainBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

class BrainSwimStraight : public BrainBase {
public:
    BrainSwimStraight(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
