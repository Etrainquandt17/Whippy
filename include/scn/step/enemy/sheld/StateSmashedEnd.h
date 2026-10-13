#ifndef SCN_STEP_ENEMY_SHELD_STATESMASHEDEND_H
#define SCN_STEP_ENEMY_SHELD_STATESMASHEDEND_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace sheld {

class StateSmashedEnd : public StateBase {
public:
    StateSmashedEnd(Enemy* enemy);
    virtual ~StateSmashedEnd();
    virtual void procAnim();

private:
    u32 mWait;
};

}
}
}
}

#endif
