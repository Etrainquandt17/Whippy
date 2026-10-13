#include "scn/step/sfx/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/sfx/MintSuperBackPicture.h"
#include "scn/step/sfx/MintSuperFade.h"

namespace scn {
namespace step {
namespace sfx {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperFade", "void SetBack(bool)", SetBack, &MintSuperFade::SetBack);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffect(int)", RequestEffect,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffect));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffectN(int)", RequestEffectN,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffectN));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void ReleaseEffect()", ReleaseEffect, &MintSuperBackPicture::ReleaseEffect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffect2(int)", RequestEffect2,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffect2));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffect2N(int)", RequestEffect2N,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffect2N));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void ReleaseEffect2()", ReleaseEffect2, &MintSuperBackPicture::ReleaseEffect2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffectNonStop(int)", RequestEffectNonStop,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffectNonStop));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffectNonStopN(int)", RequestEffectNonStopN,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffectNonStopN));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void ReleaseEffectNonStop()", ReleaseEffectNonStop,
                         &MintSuperBackPicture::ReleaseEffectNonStop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffectNonStop2(int)", RequestEffectNonStop2,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffectNonStop2));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void RequestEffectNonStop2N(int)", RequestEffectNonStop2N,
                         reinterpret_cast<void (*)(u32)>(&MintSuperBackPicture::RequestEffectNonStop2N));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Sfx.SuperBackPicture", "void ReleaseEffectNonStop2()", ReleaseEffectNonStop2,
                         &MintSuperBackPicture::ReleaseEffectNonStop2);
}

}}}}  // namespace scn::step::sfx::AddOnMint
