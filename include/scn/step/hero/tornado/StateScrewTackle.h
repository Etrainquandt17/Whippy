#ifndef SCN_STEP_HERO_TORNADO_STATESCREWTACKLE_H
#define SCN_STEP_HERO_TORNADO_STATESCREWTACKLE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace tornado {

class StateScrewTackle : public StateBase {
public:
    static bool TryToChangeState(Hero* hero, u32 count);

    StateScrewTackle(Hero* hero, u32 count);
    virtual ~StateScrewTackle();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    int mSubState;
    f32 mSpeedV;
    f32 mGravityRate;
    f32 mAccelVRate;
};

}}}}  // namespace scn::step::hero::tornado

#endif
