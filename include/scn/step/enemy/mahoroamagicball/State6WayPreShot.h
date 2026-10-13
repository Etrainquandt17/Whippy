#ifndef SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATE6WAYPRESHOT_H
#define SCN_STEP_ENEMY_MAHOROAMAGICBALL_STATE6WAYPRESHOT_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace mahoroamagicball {

// TODO: stub
class State6WayPreShot : public StateBase {
public:
    State6WayPreShot(Enemy* enemy, const hel::math::Vector3& pos, f32 _18, f32 angle);
};

}
}
}
}

#endif
