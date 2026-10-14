#include "scn/step/boss/doubter/StateEtherJumpFall.h"

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
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateEtherJumpFall::StateEtherJumpFall(Boss* boss) : StateBase(boss) {
    obj().footState().setAir();
    Utility::ControlHateOnAction(obj());
    obj().hateCtrl().fix();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(34);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
}

StateEtherJumpFall::~StateEtherJumpFall() {}

void StateEtherJumpFall::procAnim() {}

void StateEtherJumpFall::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().airDecelFall(param._16C, param._170);
}

void StateEtherJumpFall::procFixPos() {
    const Param& param = obj().param().doubter();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        Vector2 pos = param._24;
        Vector2 speed = param._2C;
        Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
        pos.x *= -1.0f;
        speed.x *= -1.0f;
        Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
        obj().soundSE().normal().start(Utility::IsVariationExtra(obj()) ? 0x325 : 0x33B);
        obj().brainCtrl().toValid();
    }
}

}}}}  // namespace scn::step::boss::doubter
