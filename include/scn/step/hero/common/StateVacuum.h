#ifndef SCN_STEP_HERO_COMMON_STATEVACUUM_H
#define SCN_STEP_HERO_COMMON_STATEVACUUM_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

// TODO: the rest of the class, when the unit is written.
class StateVacuum : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
    StateVacuum(Hero* hero);
};

}}}}  // namespace scn::step::hero::common

#endif
