#include "scn/step/gimmick/AddOnMint.h"

#include "scn/step/gimmick/areaevent/AddOnMint.h"
#include "scn/step/gimmick/challengedoor/AddOnMint.h"
#include "scn/step/gimmick/lvmapdoor/AddOnMint.h"
#include "scn/step/gimmick/monitor/AddOnMint.h"
#include "scn/step/gimmick/shipevent/AddOnMint.h"

namespace scn {
namespace step {
namespace gimmick {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    areaevent::AddOnMint::RegisterAll(core);
    challengedoor::AddOnMint::RegisterAll(core);
    lvmapdoor::AddOnMint::RegisterAll(core);
    monitor::AddOnMint::RegisterAll(core);
    shipevent::AddOnMint::RegisterAll(core);
}

}}}}  // namespace scn::step::gimmick::AddOnMint
