#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLSHIELD_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLSHIELD_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class StateParasolShield : public StateBase {
public:
    StateParasolShield(Hero* hero);
    virtual ~StateParasolShield();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}}}}  // namespace scn::step::hero::parasol

#endif
