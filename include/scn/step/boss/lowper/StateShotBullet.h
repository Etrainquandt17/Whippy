#ifndef SCN_STEP_BOSS_LOWPER_STATESHOTBULLET_H
#define SCN_STEP_BOSS_LOWPER_STATESHOTBULLET_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/ScriptKind.h"
#include "scn/step/enemy/lowperbullet/VariationKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class StateShotBullet : public StateBase {
public:
    StateShotBullet(Boss* boss, ScriptKind kind, f32 angle, enemy::lowperbullet::VariationKind variation, u32 _5);
    virtual ~StateShotBullet();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqShotBullet();
    f32 mAngle;
    enemy::lowperbullet::VariationKind mVariation;
    u32 _10;
};

}
}
}
}

#endif
