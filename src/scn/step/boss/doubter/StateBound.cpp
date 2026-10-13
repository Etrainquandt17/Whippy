#include "scn/step/boss/doubter/StateBound.h"

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
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateWait.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateBound::StateBound(Boss* boss, const hel::math::Vector2& speed, u32 count) : StateBase(boss), mCount(count) {
    obj().footState().setAir();
    obj().model().reqScript(8);
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    hel::math::Vector3 velocity = speed.toVector3();
    velocity.x *= obj().target().getSign();
    obj().move().setVelocity(velocity);
}

StateBound::~StateBound() {}

void StateBound::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateBound::procMove() {
    if (obj().move().velocity().y <= 0.0f && mCount != 0) {
        mCount--;
        obj().move().airDecelFall(obj().param().doubter()._14, obj().param().doubter()._68);
    } else {
        obj().move().airDecelFall(obj().param().doubter()._14, obj().param().doubter()._18);
    }
}

void StateBound::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

}
}
}
}
