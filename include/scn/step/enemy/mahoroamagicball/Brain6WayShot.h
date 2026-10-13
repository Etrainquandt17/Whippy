#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAIN6WAYSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_BRAIN6WAYSHOT_H

#include "scn/step/enemy/BrainBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

class Brain6WayShot : public BrainBase {
public:
    Brain6WayShot(Enemy& enemy);
    virtual bool onStart();
};

}
}
}
}

#endif
