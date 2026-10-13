#ifndef SCN_STEP_HERO_SLEEP_SLEEP_H
#define SCN_STEP_HERO_SLEEP_SLEEP_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace sleep {

class Sleep : public AbilityBase {
public:
    Sleep(Component& component, Hero& hero);
    virtual ~Sleep();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onGetEventItem();
    virtual void onStartClearDanceExternal();
    virtual void onStartDemo();

private:
    void clearAbility();

    bool mIsSetup;
};

}}}}  // namespace scn::step::hero::sleep

#endif
