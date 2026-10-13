#ifndef SCN_STEP_HERO_SWORD_STATESWORDMETEORLANDING_H
#define SCN_STEP_HERO_SWORD_STATESWORDMETEORLANDING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordMeteorLanding : public StateBase {
public:
    StateSwordMeteorLanding(Hero* hero);
    virtual ~StateSwordMeteorLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::sword

#endif
