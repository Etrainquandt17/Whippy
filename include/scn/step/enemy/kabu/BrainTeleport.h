#ifndef SCN_STEP_ENEMY_KABU_BRAINTELEPORT_H
#define SCN_STEP_ENEMY_KABU_BRAINTELEPORT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

class BrainTeleport : public BrainBase {
public:
    BrainTeleport(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
