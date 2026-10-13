#ifndef SCN_STEP_HERO_COMMON_STATESQUAT_H
#define SCN_STEP_HERO_COMMON_STATESQUAT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateSquat : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSquat(Hero* hero);
    virtual ~StateSquat();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::hero::common

#endif
