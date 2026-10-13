#ifndef SCN_STEP_HERO_HIGHJUMP_HIGHJUMP_H
#define SCN_STEP_HERO_HIGHJUMP_HIGHJUMP_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class Highjump : public AbilityBase {
public:
    Highjump(Component& component, Hero& hero);
    virtual ~Highjump();
    virtual void setup();
    virtual bool tryToChangeState();

private:
    bool mIsSetup;
};

}}}}  // namespace scn::step::hero::highjump

#endif
