#ifndef SCN_STEP_ENEMY_COMMON_STATEMAHOROA2CALLINGSHOTSHOT_H
#define SCN_STEP_ENEMY_COMMON_STATEMAHOROA2CALLINGSHOTSHOT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateMahoroa2CallingShotShot : public StateBase {
public:
    StateMahoroa2CallingShotShot(Enemy* enemy);
    virtual ~StateMahoroa2CallingShotShot();
};

}
}
}
}

#endif
