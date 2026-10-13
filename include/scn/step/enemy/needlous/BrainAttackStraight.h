#ifndef SCN_STEP_ENEMY_NEEDLOUS_BRAINATTACKSTRAIGHT_H
#define SCN_STEP_ENEMY_NEEDLOUS_BRAINATTACKSTRAIGHT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

class BrainAttackStraight : public BrainBase {
public:
    BrainAttackStraight(Enemy& enemy);
    virtual bool onRecover();
    virtual bool onLanding();
    virtual void update();

private:
    void mfChangeWalkStraight();
    
    u32 mFrame;
};

}
}
}
}

#endif
