#ifndef SCN_STEP_HERO_BEAM_BEAM_H
#define SCN_STEP_HERO_BEAM_BEAM_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace beam {

class Beam : public AbilityBase {
public:
    Beam(Component& component, Hero& hero);
    virtual ~Beam();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();
    virtual void procAnim();

private:
    bool mIsSetup;
};

}}}}  // namespace scn::step::hero::beam

#endif
