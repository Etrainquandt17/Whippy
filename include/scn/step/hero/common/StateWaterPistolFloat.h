#ifndef SCN_STEP_HERO_COMMON_STATEWATERPISTOLFLOAT_H
#define SCN_STEP_HERO_COMMON_STATEWATERPISTOLFLOAT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateWaterPistolFloat : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateWaterPistolFloat(Hero* hero);
    virtual ~StateWaterPistolFloat();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::common

#endif
