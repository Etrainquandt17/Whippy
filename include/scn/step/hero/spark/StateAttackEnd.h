#ifndef SCN_STEP_HERO_SPARK_STATEATTACKEND_H
#define SCN_STEP_HERO_SPARK_STATEATTACKEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {

class StateAttackEnd : public StateBase {
public:
    StateAttackEnd(Hero* hero);
    virtual ~StateAttackEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::spark

#endif
