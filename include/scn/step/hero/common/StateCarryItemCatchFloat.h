#ifndef SCN_STEP_HERO_COMMON_STATECARRYITEMCATCHFLOAT_H
#define SCN_STEP_HERO_COMMON_STATECARRYITEMCATCHFLOAT_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateCarryItemCatchFloat : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCarryItemCatchFloat(Hero* hero);
    virtual ~StateCarryItemCatchFloat();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::common

#endif
