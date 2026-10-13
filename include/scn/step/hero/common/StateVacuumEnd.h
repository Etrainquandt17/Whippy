#ifndef SCN_STEP_HERO_COMMON_STATEVACUUMEND_H
#define SCN_STEP_HERO_COMMON_STATEVACUUMEND_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateVacuumEnd : public StateBase {
public:
    StateVacuumEnd(Hero* hero);
    virtual ~StateVacuumEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::common

#endif
