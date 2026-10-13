#ifndef SCN_STEP_ENEMY_NEEDLOUS_STATEIDLING_H
#define SCN_STEP_ENEMY_NEEDLOUS_STATEIDLING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace needlous {

class StateIdling : public StateBase {
public:
    StateIdling(Enemy* enemy);
    virtual ~StateIdling();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
