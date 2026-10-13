#ifndef SCN_STEP_ENEMY_WADDLEDEE_STATEWAIT_H
#define SCN_STEP_ENEMY_WADDLEDEE_STATEWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

class StateWait : public StateBase {
public:
    StateWait(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void setLoopLimit();

private:
    u32 mLoopCount;
    u32 mLoopLimit;
    bool mIsLoop;
};

}
}
}
}

#endif
