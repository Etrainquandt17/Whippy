#ifndef SCN_STEP_BOSS_LOWPER_STATESHOTBULLETSTART_H
#define SCN_STEP_BOSS_LOWPER_STATESHOTBULLETSTART_H

#include "hel/math/Vector2.h"
#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateShotBulletStart : public StateBase {
public:
    StateShotBulletStart(Boss* boss, f32 height);
    virtual ~StateShotBulletStart();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    hel::math::Vector2 mPos;
    u32 _10;
    f32 _14;
};

}
}
}
}

#endif
