#ifndef SCN_STEP_HERO_SWORD_STATESWORDUNDERTHRUSTLANDING_H
#define SCN_STEP_HERO_SWORD_STATESWORDUNDERTHRUSTLANDING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordUnderThrustLanding : public StateBase {
public:
    StateSwordUnderThrustLanding(Hero* hero);
    virtual ~StateSwordUnderThrustLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::sword

#endif
