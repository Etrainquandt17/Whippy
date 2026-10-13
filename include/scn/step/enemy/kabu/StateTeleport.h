#ifndef SCN_STEP_ENEMY_KABU_STATETELEPORT_H
#define SCN_STEP_ENEMY_KABU_STATETELEPORT_H

#include "scn/step/enemy/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

class StateTeleport : public StateBase {
public:
    StateTeleport(Enemy* enemy);
    virtual ~StateTeleport();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void blinkModel();

private:
    // TODO: name the steps.
    int mStep;
    f32 mSpeedH;
    f32 mSpeedV;
    f32 mAngle;
    u32 mWaitFrame;
    u32 mFrame;
    u32 mMoveFrame;
    bool mIsHit;
};

}}}}  // namespace scn::step::enemy::kabu

#endif
