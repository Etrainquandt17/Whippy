#ifndef SCN_STEP_ENEMY_LOWPERBULLET_STATEHOMING_H
#define SCN_STEP_ENEMY_LOWPERBULLET_STATEHOMING_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace lowperbullet {

class StateHoming : public StateBase {
public:
    StateHoming(Enemy* enemy);
    virtual ~StateHoming();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector3 mDir;
};

}
}
}
}

#endif
