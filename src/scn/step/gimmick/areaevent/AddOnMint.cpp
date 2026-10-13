#include "scn/step/gimmick/areaevent/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/gimmick/areaevent/AreaEvent.h"
#include "scn/step/gimmick/areaevent/MintAreaEvent.h"

namespace scn {
namespace step {
namespace gimmick {
namespace areaevent {

namespace {

int t_getNextSphereUnlockDemo() {
    return MintAreaEvent::Obj().getNextSphereUnlockDemo();
}

void t_setEventEnd(bool isEnd) {
    MintAreaEvent::Obj().setEventEnd(isEnd);
}

void t_setZoomSphereUnlock(int index) {
    MintAreaEvent::Obj().setZoomSphereUnlock(index);
}

void t_setZoomInduction() {
    MintAreaEvent::Obj().setZoomInduction();
}

void t_setZoom(f32 a, f32 b, f32 c, f32 d) {
    MintAreaEvent::Obj().setZoom(a, b, c, d);
}

void t_unsetZoom() {
    MintAreaEvent::Obj().unsetZoom();
}

void t_doorUnlock(int index) {
    MintAreaEvent::Obj().doorUnlock(index);
}

bool t_isUnlockEnd(int index) {
    return MintAreaEvent::Obj().isUnlockEnd(index);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "int GetNextSphereUnlockDemo()", GetNextSphereUnlockDemo, &t_getNextSphereUnlockDemo);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "void SetEventEnd(bool)", SetEventEnd, &t_setEventEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "void SetZoomSphereUnlock(int)", SetZoomSphereUnlock,
                         reinterpret_cast<void (*)(u32)>(t_setZoomSphereUnlock));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "void SetZoomInduction()", SetZoomInduction, &t_setZoomInduction);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "void SetZoom(float,float,float,float)", SetZoom, &t_setZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "void UnsetZoom()", UnsetZoom, &t_unsetZoom);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "void DoorUnlock(int)", DoorUnlock,
                         reinterpret_cast<void (*)(u32)>(t_doorUnlock));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.AreaEvent.Custom", "bool IsUnlockEnd(int)", IsUnlockEnd, &t_isUnlockEnd);
}

}
}
}
}
}
