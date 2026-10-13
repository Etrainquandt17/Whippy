#ifndef SCN_STEP_HERO_WING_WING_H
#define SCN_STEP_HERO_WING_WING_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace wing {

class Wing : public AbilityBase {
public:
    Wing(Component& component, Hero& hero);
    virtual ~Wing();
    virtual void setup();
    virtual bool tryToChangeStateOnInterval();
    virtual bool tryToChangeState();

private:
    bool mIsSetup;
};

}}}}  // namespace scn::step::hero::wing

#endif
