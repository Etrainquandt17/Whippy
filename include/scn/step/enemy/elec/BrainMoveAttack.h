#ifndef SCN_STEP_ENEMY_ELEC_BRAINMOVEATTACK_H
#define SCN_STEP_ENEMY_ELEC_BRAINMOVEATTACK_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

class BrainMoveAttack : public BrainBase {
public:
    BrainMoveAttack(Enemy& enemy);
    virtual bool onStart();
    virtual bool onRecover();
    virtual void update();

private:
    bool mIsFound;
};

}
}
}
}

#endif
