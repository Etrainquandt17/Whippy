#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINBOMB_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINBOMB_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

class BrainBomb : public BrainBase {
public:
    BrainBomb(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
