#ifndef SCN_STEP_BOSS_GOLIATH_STATESWOOPLANDING_H
#define SCN_STEP_BOSS_GOLIATH_STATESWOOPLANDING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateSwoopLanding : public StateBase {
public:
    StateSwoopLanding(Boss* boss);
    virtual ~StateSwoopLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void generateStarEffect();
};

}}}}  // namespace scn::step::boss::goliath

#endif
