#ifndef SCN_STEP_ENEMY_SCARFY_STATEFACECHANGE_H
#define SCN_STEP_ENEMY_SCARFY_STATEFACECHANGE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace scarfy {

class StateFaceChange : public StateBase {
public:
    StateFaceChange(Enemy* enemy);
    virtual ~StateFaceChange();
    virtual void procAnim();
    virtual void procMove();

private:
    bool mIsEnd;
    bool mIsFlipped;
    u32 mFrame;
};

}
}
}
}

#endif
