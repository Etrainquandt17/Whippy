#ifndef SCN_STEP_ENEMY_ROCKY_STATELANDING_H
#define SCN_STEP_ENEMY_ROCKY_STATELANDING_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace rocky {

class StateLanding : public StateBase {
public:
    StateLanding(Enemy* enemy);
    virtual ~StateLanding();
    virtual void procAnim();
    virtual void procFixPos();

private:
    f32 mNormalX;
    bool mIsEffectRequested;
};

}
}
}
}

#endif
