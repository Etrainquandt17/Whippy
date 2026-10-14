#include "scn/step/enemy/landiasingle/Custom.h"

#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/enemy/landiasingle/StateDead.h"
#include "scn/step/enemy/landiasingle/StatePreDead.h"
#include "scn/step/enemy/landiasingle/StateWait.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mFlagActionEnd(false), mFormationPassMoveShotCount(0), mFireRainCount(0), mGrandCrossStopCount(0),
      mHeadAngleCtrl(enemy) {}

bool Custom::onInit() {
    const ParamData& param = obj().param().landiasingle();
    obj().captureReceiver().setCanCapture(false);
    obj().mapColl().setValid(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().objColl().clearBodyColl();
    obj().footState().setAir();
    obj().culling().setValid(false);
    obj().shadow().changeDiameter(param._c);
    obj().shadow().changeMaxHeight(param._10);
    obj().shadow().setVisibility(true);
    switch (obj().level()) {
    case 0:
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x365), 3);
        break;
    case 1:
    case 2:
    case 3:
        obj().model().model().nodes().at(NODE_KIND_CROWN).setVisibilityBelow(false);
        break;
    }
    obj().location().setToCenter(Vector2(param._4).toVector3());
    if (obj().kind() == 0x89) {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(&obj(), true);
        return true;
    }
    obj().stateChanger().setNextState<StateDead, Enemy*>(&obj());
    return true;
}

void Custom::onProcFixPos() {
    mHeadAngleCtrl.update();
    if (obj().signal().isValid() && obj().signal().get() == 0x18) {
        obj().signal().clear();
        obj().stateChanger().setNextState<StatePreDead, Enemy*>(&obj());
    }
}

void Custom::incrementFormationPassMoveShotCount() {
    mFormationPassMoveShotCount++;
}

void Custom::resetFormationPassMoveShotCount() {
    mFormationPassMoveShotCount = 0;
}

// TODO: the link dropped this one and the next: the bodies are guesses of the right size.
bool Custom::isFormationPassMoveShotHalfEnd() {
    return mFormationPassMoveShotCount >= 2;
}

bool Custom::isFormationPassMoveShotNoMove() {
    return mFormationPassMoveShotCount == 1;
}

void Custom::incrementFireRainCount() {
    mFireRainCount++;
}

void Custom::resetFireRainCount() {
    mFireRainCount = 0;
}

u32 Custom::fireRainCount() {
    return mFireRainCount;
}

void Custom::incrementGrandCrossStopCount() {
    mGrandCrossStopCount++;
}

void Custom::resetGrandCrossStopCount() {
    mGrandCrossStopCount = 0;
}

u32 Custom::grandCrossStopCount() {
    return mGrandCrossStopCount;
}

bool Custom::flagActionEnd() const {
    return mFlagActionEnd;
}

void Custom::setFlagActionEnd() {
    mFlagActionEnd = true;
}

void Custom::resetFlagActionEnd() {
    mFlagActionEnd = false;
}

HeadAngleCtrl& Custom::headAngleCtrl() {
    return mHeadAngleCtrl;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::landiasingle
