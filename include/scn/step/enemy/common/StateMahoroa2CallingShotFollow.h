#ifndef SCN_STEP_ENEMY_COMMON_STATEMAHOROA2CALLINGSHOTFOLLOW_H
#define SCN_STEP_ENEMY_COMMON_STATEMAHOROA2CALLINGSHOTFOLLOW_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateMahoroa2CallingShotFollow : public StateBase {
public:
    StateMahoroa2CallingShotFollow(Enemy* enemy, bool _8);
    virtual ~StateMahoroa2CallingShotFollow();
};

}
}
}
}

#endif
