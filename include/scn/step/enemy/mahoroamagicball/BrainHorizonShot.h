#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINHORIZONSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINHORIZONSHOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainHorizonShot : public BrainBase {
public:
    BrainHorizonShot(Enemy& enemy, bool _1);
    virtual bool onStart();

private:
    bool _8;
};

}
}
}
}

#endif
