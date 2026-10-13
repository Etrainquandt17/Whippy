#ifndef SCN_STEP_HERO_SPARK_STATEATTACKOVEREND_H
#define SCN_STEP_HERO_SPARK_STATEATTACKOVEREND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {

class StateAttackOverEnd : public StateBase {
public:
    StateAttackOverEnd(Hero* hero);
    virtual ~StateAttackOverEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::spark

#endif
