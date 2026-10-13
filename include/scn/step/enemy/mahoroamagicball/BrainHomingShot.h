#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINHOMINGSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINHOMINGSHOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainHomingShot : public BrainBase {
public:
    BrainHomingShot(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
