#ifndef SCN_STEP_ENEMY_TSUKIKAGE_BRAINGROUND_H
#define SCN_STEP_ENEMY_TSUKIKAGE_BRAINGROUND_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

class BrainGround : public BrainBase {
public:
    BrainGround(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
