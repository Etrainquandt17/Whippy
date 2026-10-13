#ifndef SCN_STEP_HERO_COMMON_STATEPLANCHERBOUND_H
#define SCN_STEP_HERO_COMMON_STATEPLANCHERBOUND_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StatePlancherBound : public StateBase {
public:
    StatePlancherBound(Hero* hero);
    virtual ~StatePlancherBound();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::common

#endif
