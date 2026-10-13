#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEHOMINGSHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATEHOMINGSHOT_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

// TODO: stub
class StateHomingShot : public StateBase {
public:
    StateHomingShot(Enemy* enemy);
};

}
}
}
}

#endif
