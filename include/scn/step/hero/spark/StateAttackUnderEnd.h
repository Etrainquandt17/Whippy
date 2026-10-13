#ifndef SCN_STEP_HERO_SPARK_STATEATTACKUNDEREND_H
#define SCN_STEP_HERO_SPARK_STATEATTACKUNDEREND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {

class StateAttackUnderEnd : public StateBase {
public:
    StateAttackUnderEnd(Hero* hero);
    virtual ~StateAttackUnderEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::spark

#endif
