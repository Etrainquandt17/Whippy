#ifndef SCN_STEP_ENEMY_SCARFY_BRAINFLYUPDOWN_H
#define SCN_STEP_ENEMY_SCARFY_BRAINFLYUPDOWN_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

class BrainFlyUpDown : public BrainBase {
public:
    BrainFlyUpDown(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
};

}
}
}
}

#endif
