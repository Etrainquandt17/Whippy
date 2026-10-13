#ifndef SCN_STEP_HERO_FIRE_FIRE_H
#define SCN_STEP_HERO_FIRE_FIRE_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace fire {

class Fire : public AbilityBase {
public:
    Fire(Component& component, Hero& hero);
    virtual ~Fire();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void procAnim();

    bool isContinueBurning();
    void endContinueBurning();

private:
    void requestHatFire();
    void releaseHatFire();

    bool mIsSetup;
    bool mIsHatFire;
    u32 mBurningCount;
};

}}}}  // namespace scn::step::hero::fire

#endif
