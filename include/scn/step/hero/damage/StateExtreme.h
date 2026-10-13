#ifndef SCN_STEP_HERO_DAMAGE_STATEEXTREME_H
#define SCN_STEP_HERO_DAMAGE_STATEEXTREME_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateExtreme : public StateBase {
public:
    // TODO: name the values.
    enum DamageLevel {
        DAMAGE_LEVEL_0,
        DAMAGE_LEVEL_1
    };

    StateExtreme(Hero* hero, DamageLevel level);
    virtual ~StateExtreme();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    bool mIsLanded;
    u32 mWait;
    u32 mFrame;
    u32 mEndFrame;
};

}}}}  // namespace scn::step::hero::damage

#endif
