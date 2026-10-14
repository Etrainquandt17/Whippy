#include "scn/step/boss/doubter/StateJump.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/ScriptKind.h"
#include "scn/step/boss/doubter/StateLanding.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateJump::StateJump(Boss* boss, const Vector2& speed, u32 count) : StateBase(boss), mCount(count) {
    obj().footState().setAir();
    obj().model().reqScript(10);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    Vector3 velocity = speed.toVector3();
    velocity.x *= obj().target().getSign();
    obj().move().setVelocity(velocity);
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateJump::procMove() {
    if (obj().move().velocity().y <= 0.0f && mCount != 0) {
        mCount--;
        obj().move().airDecelFall(obj().param().doubter()._14, obj().param().doubter()._74);
    } else {
        obj().move().airDecelFall(obj().param().doubter()._14, obj().param().doubter()._18);
    }
}

void StateJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        Vector2 pos = obj().param().doubter()._24;
        Vector2 speed = obj().param().doubter()._2C;
        Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
        pos.x *= -1.0f;
        speed.x *= -1.0f;
        Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        obj().stateChanger().setNextState<StateLanding, Boss*, ScriptKind>(objPtr(), static_cast<ScriptKind>(5));
    }
}

}}}}  // namespace scn::step::boss::doubter
