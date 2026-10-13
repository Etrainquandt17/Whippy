#ifndef SCN_STEP_HERO_COMMON_STATESLIDINGHIT_H
#define SCN_STEP_HERO_COMMON_STATESLIDINGHIT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateSlidingHit : public StateBase {
public:
    StateSlidingHit(Hero* hero);
    virtual ~StateSlidingHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::common

#endif
