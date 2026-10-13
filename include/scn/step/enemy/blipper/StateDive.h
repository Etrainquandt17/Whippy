#ifndef SCN_STEP_ENEMY_BLIPPER_STATEDIVE_H
#define SCN_STEP_ENEMY_BLIPPER_STATEDIVE_H

#include "scn/step/chara/FreeRotController.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace blipper {

class StateDive : public StateBase {
public:
    StateDive(Enemy* enemy);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mSpeedV;
    f32 mDir;
    chara::FreeRotController mRotCtrl;
};

}
}
}
}

#endif
