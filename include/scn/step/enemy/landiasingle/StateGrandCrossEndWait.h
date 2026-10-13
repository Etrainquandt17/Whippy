#ifndef SCN_STEP_ENEMY_LANDIASINGLE_STATEGRANDCROSSENDWAIT_H
#define SCN_STEP_ENEMY_LANDIASINGLE_STATEGRANDCROSSENDWAIT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace landiasingle {

class StateGrandCrossEndWait : public StateBase {
public:
    StateGrandCrossEndWait(Enemy* enemy);
    virtual ~StateGrandCrossEndWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void setCustomMtx(f32 rate);
    
    u32 mFrame;
};

}
}
}
}

#endif
