#ifndef SCN_STEP_HERO_SUPERICE_SUPERICE_H
#define SCN_STEP_HERO_SUPERICE_SUPERICE_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace superice {

class SuperIce : public AbilityBase {
public:
    SuperIce(Component& component, Hero& hero);
    virtual ~SuperIce();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void procAnim();
    virtual bool isDepleted() const;

private:
    bool mIsSetup;
};

}}}}  // namespace scn::step::hero::superice

#endif
