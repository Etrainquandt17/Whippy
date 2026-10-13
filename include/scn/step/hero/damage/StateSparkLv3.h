#ifndef SCN_STEP_HERO_DAMAGE_STATESPARKLV3_H
#define SCN_STEP_HERO_DAMAGE_STATESPARKLV3_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateSparkLv3 : public StateBase {
public:
    StateSparkLv3(Hero* hero);
    virtual ~StateSparkLv3();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mRot;
    bool mIsLanded;
    u32 mWait;
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::damage

#endif
