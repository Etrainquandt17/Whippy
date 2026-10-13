#ifndef SCN_STEP_ENEMY_DAMAGE_STATEPARASOLRELEASE_H
#define SCN_STEP_ENEMY_DAMAGE_STATEPARASOLRELEASE_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace damage {

class StateParasolRelease : public StateBase {
public:
    StateParasolRelease(Enemy* enemy, u64 ownerUid, u32 endFrame);
    virtual ~StateParasolRelease();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    f32 mRot;
    u32 mFrame;
    u32 mEndFrame;
    u32 mWait;
};

}
}
}
}

#endif
