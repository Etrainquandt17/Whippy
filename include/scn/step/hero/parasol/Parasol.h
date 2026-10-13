#ifndef SCN_STEP_HERO_PARASOL_PARASOL_H
#define SCN_STEP_HERO_PARASOL_PARASOL_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class Parasol : public AbilityBase {
public:
    Parasol(Component& component, Hero& hero);
    virtual ~Parasol();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();
    virtual void procAnim();

private:
    bool mIsSetup;
    bool mIsParachute;
    bool mIsParachuteKeep;
};

}}}}  // namespace scn::step::hero::parasol

#endif
