#include "scn/step/boss/moundeath/StateMoveForward.h"

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

StateMoveForward::StateMoveForward(Boss* boss) : StateBase(boss), mCount(0) {
    obj().footState().setGround();
    obj().model().reqScript(6);
    obj().brainCtrl().toValid();
}

StateMoveForward::~StateMoveForward() {}

void StateMoveForward::procAnim() {
    const Param& param = obj().param().moundeath();
    if (++mCount % param._60 == 0) {
        Utility::TurnHatedHero(obj());
    }
}

void StateMoveForward::procMove() {
    const Param& param = obj().param().moundeath();
    f32 total = obj().model().anim().totalFrame();
    f32 t = obj().model().anim().frame() / total;
    int deg = static_cast<int>(70.0f + 720.0f * t) % 360;
    f32 rate = 0.5f * (1.0f + hel::math::Math::SinDegF(deg));
    rate *= rate;
    obj().move().groundAccel(obj().target().isRightDir(), gobj::MoveParamAccel::Create(param._54 * rate, param._58 * rate, param._5C));
}

void StateMoveForward::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}
}
}
}
