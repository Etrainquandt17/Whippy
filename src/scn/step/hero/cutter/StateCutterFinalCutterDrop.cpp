#include "scn/step/hero/cutter/StateCutterFinalCutterDrop.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "scn/step/hero/CutterParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/cutter/StateCutterFinalCutterLanding.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

StateCutterFinalCutterDrop::StateCutterFinalCutterDrop(Hero* hero)
    : StateBase(hero)
    , mFrame(0) {
    obj().footState().setAir();
    obj().model().script().start(0x90);
    obj().move().setSpeedH(obj().param().cutter()._40);
    obj().move().setSpeedV(obj().param().cutter()._44);
    obj().invincible().setPerm();
}

StateCutterFinalCutterDrop::~StateCutterFinalCutterDrop() {
}

void StateCutterFinalCutterDrop::procAnim() {
    mFrame++;
}

void StateCutterFinalCutterDrop::procMove() {
    gobj::MoveParamFall fall = obj().param().cutter()._50;
    if (mFrame > obj().param().cutter()._48) {
        fall = obj().param().cutter()._5C;
    }
    obj().move().airDecelFall(obj().param().cutter()._4C, fall);
}

void StateCutterFinalCutterDrop::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<StateCutterFinalCutterLanding, Hero*>(objPtr());
    }
}

}}}}  // namespace scn::step::hero::cutter
