#include "scn/step/core/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/core/MintBGMController.h"

namespace scn {
namespace step {
namespace core {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Core.BGMController", "void Request(int,int,bool)", Request, &MintBGMController::Request);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Core.BGMController", "void Unrequest(int)", Unrequest, &MintBGMController::Unrequest);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Core.BGMController", "void Pause(int)", Pause, &MintBGMController::Pause);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Core.BGMController", "void Unpause(int)", Unpause, &MintBGMController::Unpause);
}

}}}}  // namespace scn::step::core::AddOnMint
