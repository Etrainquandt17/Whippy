#ifndef SCN_STEP_ENEMY_PIERCE_STATEFLYAROUND_H
#define SCN_STEP_ENEMY_PIERCE_STATEFLYAROUND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace pierce {

// TODO: stub
class StateFlyAround : public StateBase {
public:
    StateFlyAround(Enemy* enemy);
};

}
}
}
}

#endif
