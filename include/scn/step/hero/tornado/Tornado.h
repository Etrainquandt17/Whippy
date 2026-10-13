#ifndef SCN_STEP_HERO_TORNADO_TORNADO_H
#define SCN_STEP_HERO_TORNADO_TORNADO_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace tornado {

class Tornado : public AbilityBase {
public:
    Tornado(Component& component, Hero& hero);
    virtual ~Tornado();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void procAnim();

private:
    void endContinueScrewTackle();
    void requestHatWind();
    void releaseHatWind();

    bool mIsSetup;
    bool mIsHatWind;
    u32 mScrewTackleCount;
};

}}}}  // namespace scn::step::hero::tornado

#endif
