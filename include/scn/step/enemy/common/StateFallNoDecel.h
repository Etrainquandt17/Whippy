#ifndef SCN_STEP_ENEMY_COMMON_STATEFALLNODECEL_H
#define SCN_STEP_ENEMY_COMMON_STATEFALLNODECEL_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace common {

class StateFallNoDecel : public StateBase {
public:
    StateFallNoDecel(Enemy* enemy);
    virtual ~StateFallNoDecel();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
