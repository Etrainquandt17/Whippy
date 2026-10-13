#ifndef SCN_STEP_HERO_SWORD_STATESWORDTHRUSTEND_H
#define SCN_STEP_HERO_SWORD_STATESWORDTHRUSTEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordThrustEnd : public StateBase {
public:
    StateSwordThrustEnd(Hero* hero);
    virtual ~StateSwordThrustEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::sword

#endif
