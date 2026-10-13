#include "scn/step/camera/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MintCameraController.h"
#include "scn/step/camera/MintZoomQuake.h"
#include "scn/step/camera/ZoomQuake.h"

namespace scn {
namespace step {
namespace camera {

namespace {

void t_CameraController_ReqQuake(int kind) {
    MintCameraController::Obj().reqQuake(static_cast<QuakeKind>(kind));
}

void t_CameraController_ReqZoomQuake(int kind) {
    MintCameraController::Obj().reqZoomQuake(static_cast<ZoomQuakeKind>(kind));
}

void t_ZoomQuake_Method_SetOffs(f32 offs) {
    MintZoomQuake::Obj().setOffs(offs);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Camera.CameraController", "void ReqQuake(int)", ReqQuake, &t_CameraController_ReqQuake);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Camera.CameraController", "void ReqZoomQuake(int)", ReqZoomQuake, &t_CameraController_ReqZoomQuake);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Camera.ZoomQuake.Method", "void SetOffs(float)", SetOffs, &t_ZoomQuake_Method_SetOffs);
}

}
}
}
}
