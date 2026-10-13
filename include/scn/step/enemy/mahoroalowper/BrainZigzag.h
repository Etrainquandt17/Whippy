#ifndef SCN_STEP_ENEMY_MAHOROALOWPER_BRAINZIGZAG_H
#define SCN_STEP_ENEMY_MAHOROALOWPER_BRAINZIGZAG_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroalowper {

class BrainZigzag : public BrainBase {
public:
    BrainZigzag(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
