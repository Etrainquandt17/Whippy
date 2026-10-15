#ifndef SCN_STEP_BOSS_GOLIATH_STATEROCKETEND_H
#define SCN_STEP_BOSS_GOLIATH_STATEROCKETEND_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateRocketEnd : public StateBase {
public:
    StateRocketEnd(Boss* boss);
    virtual ~StateRocketEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void generateStarEffect();
};

}}}}  // namespace scn::step::boss::goliath

#endif
