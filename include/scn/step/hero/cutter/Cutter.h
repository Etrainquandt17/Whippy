#ifndef SCN_STEP_HERO_CUTTER_CUTTER_H
#define SCN_STEP_HERO_CUTTER_CUTTER_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class Cutter : public AbilityBase {
public:
    Cutter(Component& component, Hero& hero);
    virtual ~Cutter();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();

private:
    bool mIsSetup;
};

}}}}  // namespace scn::step::hero::cutter

#endif
