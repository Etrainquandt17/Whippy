#ifndef SCN_STEP_ENEMY_SHELD_BRAINDASH_H
#define SCN_STEP_ENEMY_SHELD_BRAINDASH_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

class BrainDash : public BrainBase {
public:
    BrainDash(Enemy& enemy);
    virtual bool onLanding();
    virtual void update();
};

}
}
}
}

#endif
