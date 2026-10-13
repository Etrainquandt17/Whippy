#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLWATERDRILLEND_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLWATERDRILLEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class StateParasolWaterDrillEnd : public StateBase {
public:
    StateParasolWaterDrillEnd(Hero* hero);
    virtual ~StateParasolWaterDrillEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::parasol

#endif
