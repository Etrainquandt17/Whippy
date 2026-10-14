#include "scn/step/boss/galactaknight/StateDead.h"

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
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/HitStop.h"
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

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

namespace {

// TODO: a stand-in for a comparison that hel/math/Vector2.h does not have yet.
inline bool t_Equals(const Vector2& a, const Vector2& b) {
    return a.x == b.x && a.y == b.y;
}

}

// TODO: three registers differ: the original keeps isRight in r31, the parameters in r30 and the custom in r29;
// this gives r29, r31 and r30. The same statements match in StateDamageL, where the cast is expanded.
StateDead::StateDead(Boss* boss)
    : StateBase(boss), _8(false), mIsFirst(true), mIsStaged(false), mCount(0), mFrame(0), mRot(0.0f),
      mStartPos(boss->location().pos()), mGoalPos(), mIsBound(false) {
    const Param& param = obj().param().galactaknight();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mFrame = param._138;
    obj().hitStop().clear();
    obj().footState().setAir();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    if (obj().objColl().bodyColl().hit().isCollide()) {
        Vector2 attackPos = obj().objColl().bodyColl().damageInfo().attackPos();
        bool isRight = attackPos.x > obj().location().pos().x;
        obj().target().setIsRightDir(isRight);
    }
    mGoalPos.x = param._13C * -obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    mGoalPos.z = 0.0f;
    stagingBossDead();
}

StateDead::~StateDead() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setWhiteColorAnim();
}

void StateDead::procAnim() {
    if (!mIsStaged) {
        stagingBossDead();
        return;
    }
    if (mIsFirst) {
        mIsFirst = false;
        Utility::DisappearBossPanel(obj());
    }
    if (mCount < mFrame) {
        mCount++;
        if (mCount == mFrame && mIsBound) {
            obj().model().rotCtrl().resetRot();
            obj().model().reqScript(4);
        }
    }
    updateRotate();
    if (!_8 && obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateDead::procMove() {
    const Param& param = obj().param().galactaknight();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 sin = Math::SinDegF(180.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    if (mIsBound) {
        pos.y += param._14C * sin;
    } else {
        pos.y += param._140 * sin;
    }
    obj().location().setPos(pos);
}

void StateDead::procFixPos() {
    if (!mIsBound && mCount == mFrame) {
        const Param& param = obj().param().galactaknight();
        mIsBound = true;
        mCount = 0;
        mFrame = param._144;
        mStartPos = mGoalPos;
        mGoalPos.x += param._148 * -obj().target().getSign();
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
        obj().soundSE().normal().start(0x114);
    }
}

void StateDead::updateRotate() {
    if (mCount < mFrame) {
        if (!mIsBound) {
            mRot += 20.0f * obj().target().getSign();
            if (mRot >= 360.0f) {
                mRot -= 360.0f;
            }
            if (mRot < 0.0f) {
                mRot += 360.0f;
            }
            Vector2 velocity = obj().move().velocity().getXY();
            if (!t_Equals(velocity, Vector2::ZERO)) {
                velocity.normalize();
                f32 angle = Vector2::BASIS_Y.signedAngle(velocity);
                obj().model().rotCtrl().setRotV(57.29578f * angle);
            }
            obj().model().rotCtrl().setRotH(mRot);
        } else {
            f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
            f32 rot = Math::LinearInterpolation(90.0f, 330.0f, t);
            rot *= obj().target().getSign();
            obj().model().rotCtrl().setRotH(50.0f);
            obj().model().rotCtrl().setRotV(rot);
        }
    }
}

void StateDead::stagingBossDead() {
    if (!mIsStaged && !Utility::IsHeroDeadStop(obj())) {
        const Param& param = obj().param().galactaknight();
        mIsStaged = true;
        obj().comp().enemyManager().reqDeadAllEnemyForBoss();
        obj().comp().weaponManager().reqDeadByTeamNo(static_cast<ocoll::TeamNo>(1));
        obj().model().reqScript(0x2B);
        Utility::StagingBossDead(obj(), param._150);
        obj().effect().normal().releaseAndVanish();
    }
}

}}}}  // namespace scn::step::boss::galactaknight
