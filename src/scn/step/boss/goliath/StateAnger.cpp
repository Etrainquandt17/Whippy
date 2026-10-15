#include "scn/step/boss/goliath/StateAnger.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/info/BossPanel.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateAnger::StateAnger(Boss* boss) : StateBase(boss), mZoomHandle(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::TurnHatedHero(obj());
    obj().invincible().setPermNoFlash();
    obj().model().reqScript(0x23);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    custom.eyeCtrl().setKeepOpen();
    obj().infoBossPanel().transformStart();
}

StateAnger::~StateAnger() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().infoBossPanel().transformEnd();
    custom.eyeCtrl().startAnim();
    obj().comp().cameraController().unsetZoom(mZoomHandle);
}

void StateAnger::procAnim() {
    const Param& param = obj().param().goliath();
    if (obj().scriptTrigger().get(0)) {
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        Vector2 pos = obj().location().pos().getXY();
        f32 centerX = custom.landCtrl().getCenterX();
        pos.x = 0.2f * (pos.x - centerX) + centerX;
        pos.y += 2.0f;
        mZoomHandle = obj().comp().cameraController().setZoom(pos, param._68);
    }
    if (obj().scriptTrigger().get(1)) {
        obj().effect().back().requestN(static_cast<effect::Kind>(0x27E), 0);
        obj().effect().back().requestN(static_cast<effect::Kind>(0x27C), 0);
        obj().effect().fore().requestN(static_cast<effect::Kind>(0x27D), 0);
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        custom.hairCtrl().setAngry(true);
        custom.eyeCtrl().setAngry(true);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateAnger::procMove() {}

void StateAnger::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
