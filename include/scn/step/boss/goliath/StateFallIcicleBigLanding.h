#ifndef SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEBIGLANDING_H
#define SCN_STEP_BOSS_GOLIATH_STATEFALLICICLEBIGLANDING_H

#include "scn/step/boss/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

class StateFallIcicleBigLanding : public StateBase {
public:
    StateFallIcicleBigLanding(Boss* boss);
    virtual ~StateFallIcicleBigLanding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::boss::goliath

#endif
