#include "scn/step/boss/moundeath/StateRollJump.h"

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

StateRollJump::StateRollJump(Boss* boss, Config config) : StateBase(boss), mCount(0), mFrame(0), mStartPos(), mDistance(0.0f) {
    const Param& param = obj().param().moundeath();
    obj().footState().setAir();
    obj().model().reqScript(0x13);
    obj().guard().setType(static_cast<GuardType>(2));
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
    mStartPos = obj().location().pos().getXY();
    mDistance = Utility::GetHatedHeroPos(obj()).x - mStartPos.x;
    mDistance = mDistance > 0.0f ? hel::math::Math::Min(mDistance, param._D0) : hel::math::Math::Max(mDistance, -param._D0);
    obj().target().setIsRightDir(mDistance > 0.0f);
    if (config._0) {
        mFrame = param._C4;
    } else {
        mFrame = param._C8;
    }
}

StateRollJump::~StateRollJump() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateRollJump::procAnim() {
    const Param& param = obj().param().moundeath();
    if (mCount < mFrame) {
        mCount++;
    } else if (!obj().brainCtrl().isValid()) {
        hel::math::Vector2 pos(param._44);
        hel::math::Vector2 speed(param._4C);
        Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
        pos.x *= -1.0f;
        speed.x *= -1.0f;
        Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xA0), obj().location().pos() + pos.toVector3());
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        obj().soundSE().normal().start(0x5A5);
        obj().brainCtrl().toValid();
    }
}

void StateRollJump::procMove() {
    const Param& param = obj().param().moundeath();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    hel::math::Vector2 pos = mStartPos;
    pos.x += mDistance * hel::math::Math::SinDegF(90.0f * t);
    pos.y += param._CC * (1.0f - (1.0f - hel::math::Math::SinDegF(180.0f * t)) *
                                     ((1.0f - hel::math::Math::SinDegF(180.0f * t)) * (1.0f - hel::math::Math::SinDegF(180.0f * t))));
    obj().location().setPos(pos.toVector3());
}

void StateRollJump::procFixPos() {}

}
}
}
}
