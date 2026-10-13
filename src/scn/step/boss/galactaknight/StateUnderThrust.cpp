#include "scn/step/boss/galactaknight/StateUnderThrust.h"

#include "app/Random.h"
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
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateAttack.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
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
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateUnderThrust::StateUnderThrust(Boss* boss)
    : StateBase(boss), mFrame(0), mCount(0), mStartPos(boss->location().pos()), mGoalPos(), mIsStart(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    mFrame = (obj().location().pos().y - mGoalPos.y) / 0.4f;
    obj().model().reqScript(0x1B);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateUnderThrust::~StateUnderThrust() {}

void StateUnderThrust::procAnim() {
    if (obj().scriptTrigger().get(1)) {
        mIsStart = true;
    }
    if (mCount < mFrame) {
        if (mIsStart) {
            mCount++;
        }
    } else {
        changeStateLanding();
    }
}

void StateUnderThrust::procMove() {
    if (mIsStart) {
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
        hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, t);
        obj().location().setPos(pos);
    }
}

void StateUnderThrust::procFixPos() {}

void StateUnderThrust::changeStateLanding() {
    const Param& param = obj().param().galactaknight();
    hel::math::Vector2 pos = param._14;
    hel::math::Vector2 speed = param._24;
    pos.x *= obj().target().getSign();
    speed.x *= obj().target().getSign();
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    AttackDesc desc(static_cast<ScriptKind>(0x1C), true);
    obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(objPtr(), desc);
}

}
}
}
}
