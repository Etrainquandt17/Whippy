#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLDRILLEND_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLDRILLEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class StateParasolDrillEnd : public StateBase {
public:
    StateParasolDrillEnd(Hero* hero);
    virtual ~StateParasolDrillEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::parasol

#endif
