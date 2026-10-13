#include "scn/step/boss/moundeath/StateJump.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/moundeath/Custom.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StateJump::StateJump(Boss* boss) : StateBase(boss) {
    const Param& param = obj().param().moundeath();
    obj().footState().setAir();
    obj().model().reqScript(8);
    obj().move().setVelocity(hel::math::Vector2(param._64.x * obj().target().getSign(), param._64.y).toVector3());
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateJump::procMove() {
    const Param& param = obj().param().moundeath();
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), param._38);
}

void StateJump::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (obj().move().velocity().y < 0.0f && result.mIsHitFloor) {
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(3));
        obj().soundSE().normal().start(0x5A5);
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x48D), 1);
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

}
}
}
}
