#ifndef SCN_STEP_ENEMY_TSUKIKAGE_BRAINSMOKE_H
#define SCN_STEP_ENEMY_TSUKIKAGE_BRAINSMOKE_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

class BrainSmoke : public BrainBase {
public:
    BrainSmoke(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
