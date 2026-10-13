#ifndef SCN_STEP_HERO_MIKE_MIKE_H
#define SCN_STEP_HERO_MIKE_MIKE_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace mike {

class Mike : public AbilityBase {
public:
    Mike(Component& component, Hero& hero);
    virtual ~Mike();
    virtual void setup();
    virtual bool tryToChangeState();

private:
    bool mIsSetup;
};

}}}}  // namespace scn::step::hero::mike

#endif
