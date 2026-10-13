#include "scn/step/gimmick/monitor/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/gimmick/monitor/MintMonitor.h"
#include "scn/step/gimmick/monitor/Monitor.h"

namespace scn {
namespace step {
namespace gimmick {
namespace monitor {

namespace {

void t_seReq() {
    MintMonitor::Obj().seReq();
}

void t_viewNoise() {
    MintMonitor::Obj().viewNoise();
}

void t_viewCaution() {
    MintMonitor::Obj().viewCaution();
}

void t_viewMap() {
    MintMonitor::Obj().viewMap();
}

void t_viewShip() {
    MintMonitor::Obj().viewShip();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.Monitor.Custom", "void SeReq()", SeReq, &t_seReq);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.Monitor.Custom", "void ViewNoise()", ViewNoise, &t_viewNoise);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.Monitor.Custom", "void ViewCaution()", ViewCaution, &t_viewCaution);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.Monitor.Custom", "void ViewMap()", ViewMap, &t_viewMap);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Gimmick.Monitor.Custom", "void ViewShip()", ViewShip, &t_viewShip);
}

}}}}}  // namespace scn::step::gimmick::monitor::AddOnMint
