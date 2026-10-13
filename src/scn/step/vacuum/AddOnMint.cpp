#include "scn/step/vacuum/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/vacuum/MintAttacker.h"

namespace scn {
namespace step {
namespace vacuum {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Vacuum.Attacker", "int VacuumCount()", VacuumCount, &MintAttacker::VacuumCount);
}

}}}}  // namespace scn::step::vacuum::AddOnMint
