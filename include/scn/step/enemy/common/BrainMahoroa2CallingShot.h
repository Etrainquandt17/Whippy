#ifndef SCN_STEP_ENEMY_COMMON_BRAINMAHOROA2CALLINGSHOT_H
#define SCN_STEP_ENEMY_COMMON_BRAINMAHOROA2CALLINGSHOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class BrainMahoroa2CallingShot : public BrainBase {
public:
    BrainMahoroa2CallingShot(Enemy& enemy, bool _8);
    virtual bool onStart();
    virtual bool onRecover();

private:
    bool _8;
};

}
}
}
}

#endif
