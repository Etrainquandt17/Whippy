#include "scn/step/boss/fattybuffer/StateSwellBalloonMove.h"

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
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardFlash.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StateSwellBalloonBound.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellBalloonMove::StateSwellBalloonMove(Boss* boss, u32 count) : StateBase(boss), mCount(count) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x1D);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_6);
    obj().guard().setType(static_cast<GuardType>(4));
    obj().flash().guard().setIsValid(true);
}

StateSwellBalloonMove::~StateSwellBalloonMove() {}

void StateSwellBalloonMove::procAnim() {}

void StateSwellBalloonMove::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateSwellBalloonMove::procFixPos() {
    if (obj().mapColl().result().isHitWall() || obj().worldCage().getCorrectedDiff().x * obj().target().getSign() < 0.0f) {
        obj().stateChanger().setNextState<StateSwellBalloonBound, Boss*, StateSwellBalloonBound::Kind, u32>(
            objPtr(), StateSwellBalloonBound::KIND_WALL, mCount);
    } else if (obj().mapColl().result().isHitRoof() || obj().worldCage().getCorrectedDiff().y < 0.0f) {
        obj().stateChanger().setNextState<StateSwellBalloonBound, Boss*, StateSwellBalloonBound::Kind, u32>(
            objPtr(), StateSwellBalloonBound::KIND_ROOF, mCount);
    } else if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateSwellBalloonBound, Boss*, StateSwellBalloonBound::Kind, u32>(
            objPtr(), StateSwellBalloonBound::KIND_FLOOR, mCount);
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
