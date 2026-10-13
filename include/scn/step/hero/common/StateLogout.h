#ifndef SCN_STEP_HERO_COMMON_STATELOGOUT_H
#define SCN_STEP_HERO_COMMON_STATELOGOUT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateLogout : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateLogout(Hero* hero);
    virtual ~StateLogout();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::common

#endif
