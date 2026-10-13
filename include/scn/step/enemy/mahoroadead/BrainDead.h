#ifndef SCN_STEP_ENEMY_MAHOROADEAD_BRAINDEAD_H
#define SCN_STEP_ENEMY_MAHOROADEAD_BRAINDEAD_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroadead {

class BrainDead : public BrainBase {
public:
    BrainDead(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
