#ifndef SCN_STEP_HERO_COMMON_STATEAIRJUMP_H
#define SCN_STEP_HERO_COMMON_STATEAIRJUMP_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateAirJump : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateAirJump(Hero* hero);
    virtual ~StateAirJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::common

#endif
