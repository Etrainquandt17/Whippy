#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINDEMO_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAINDEMO_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class BrainDemo : public BrainBase {
public:
    BrainDemo(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
