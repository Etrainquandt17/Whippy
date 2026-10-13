#ifndef SCN_STEP_ENEMY_SCARFY_STATEANGERCHASE_H
#define SCN_STEP_ENEMY_SCARFY_STATEANGERCHASE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace scarfy {

// TODO: members and the overrides.
class StateAngerChase : public StateBase {
public:
    StateAngerChase(Enemy* enemy);
};

}
}
}
}

#endif
