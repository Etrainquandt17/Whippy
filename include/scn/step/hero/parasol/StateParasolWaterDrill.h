#ifndef SCN_STEP_HERO_PARASOL_STATEPARASOLWATERDRILL_H
#define SCN_STEP_HERO_PARASOL_STATEPARASOLWATERDRILL_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {

// TODO: a stand-in until the unit is written.
class StateParasolWaterDrill : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateParasolWaterDrill(Hero* hero);
};

}}}}  // namespace scn::step::hero::parasol

#endif
