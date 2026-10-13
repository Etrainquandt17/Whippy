#include "g3d/AddOnMint.h"

#include "g3d/MintModelAccessor.h"
#include "g3d/MintNodeAccessor.h"
#include "g3d/MintWrapNative.h"

namespace g3d {
namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "G3D.NodeAccessor", "void LoadWorldTrans()", LoadWorldTrans, &MintNodeAccessor::LoadWorldTrans);
    MINT_NATIVE_FUNCTION(core, "G3D.NodeAccessor", "void LoadWorldRotate()", LoadWorldRotate, &MintNodeAccessor::LoadWorldRotate);
    MINT_NATIVE_FUNCTION(core, "G3D.NodeAccessor", "void LoadWorldScale()", LoadWorldScale, &MintNodeAccessor::LoadWorldScale);
    MINT_NATIVE_FUNCTION(core, "G3D.NodeAccessor", "bool IsVisible()", IsVisible, &MintNodeAccessor::IsVisible);
    MINT_NATIVE_FUNCTION(core, "G3D.NodeAccessor", "void SetVisibility(bool)", SetVisibility, &MintNodeAccessor::SetVisibility);
    MINT_NATIVE_FUNCTION(core, "G3D.NodeAccessor", "void SetVisibilityBelow(bool)", SetVisibilityBelow, &MintNodeAccessor::SetVisibilityBelow);
    MINT_NATIVE_FUNCTION(core, "G3D.ModelAccessor", "void SetVisibility(bool)", SetVisibility, &MintModelAccessor::SetVisibility);
}

}
}
