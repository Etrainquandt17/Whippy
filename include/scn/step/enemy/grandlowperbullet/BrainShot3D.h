#ifndef SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINSHOT3D_H
#define SCN_STEP_ENEMY_GRANDLOWPERBULLET_BRAINSHOT3D_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

class BrainShot3D : public BrainBase {
public:
    BrainShot3D(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
