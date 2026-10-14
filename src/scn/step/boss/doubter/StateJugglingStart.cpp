#include "scn/step/boss/doubter/StateJugglingStart.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/CaptureCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateWaft.h"
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJugglingStart::StateJugglingStart(Boss* boss) : StateBase(boss), _8(0.0f), mCount(0), mIsCapture(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(28);
    custom.bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(2));
    if (custom.captureCtrl().isCapture()) {
        custom.jugglingCtrl().resetFollowIndex();
        mIsCapture = true;
    }
}

StateJugglingStart::~StateJugglingStart() {}

void StateJugglingStart::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        custom.jugglingCtrl().reqEnemy();
    }
    if (obj().scriptTrigger().get(1)) {
        custom.jugglingCtrl().requestJugglingThrowSE(mCount);
        custom.jugglingCtrl().setDamageHero();
        if (mCount >= 2) {
            custom.jugglingCtrl().requestJugglingCatchSE(mCount);
        }
        mCount++;
    }
    if (obj().model().isAllEnd()) {
        custom.jugglingCtrl().setIsActive(true);
        if (!mIsCapture) {
            obj().stateChanger().setNextState<StateWaft, Boss*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        }
    }
}

void StateJugglingStart::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!mIsCapture) {
        obj().location().setPos(custom.waftPositionCtrl().getNextPos());
    } else {
        obj().move().groundDecel(obj().param().doubter()._10);
    }
}

void StateJugglingStart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
