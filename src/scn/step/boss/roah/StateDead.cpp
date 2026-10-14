#include "scn/step/boss/roah/StateDead.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/ArenaCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/BodyEffectCtrl.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/weapon/Manager.h"
#include "snd/SERequestor.h"
#include "std/cmath.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateDead::StateDead(Boss* boss) : StateBase(boss), _8(false), mIsStaged(false), mIsFirst(true), mRot() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().hitStop().clear();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    stagingBossDead();
    Vector3 velocity = Vector3::BASIS_Y * -1.0f;
    velocity.rotate(static_cast<Vector3::AxisKind>(2), 0.017453292f * (param.mDeadAngle * obj().target().getSign()));
    velocity.x *= param.mDeadSpeed;
    velocity.y *= param.mDeadSpeed;
    velocity.z = param.mDeadSpeedZ;
    obj().move().setVelocity(velocity);
    if (obj().model().anim().currentG3DAnimIndex() == 10 || obj().model().anim().currentG3DAnimIndex() == 11) {
        if (custom.rotCtrl().getLocalMtxTempRot().isZeroLoose(0.00001f)) {
            mRot.x = custom.rotCtrl().getRotX();
            mRot.y = custom.rotCtrl().getRotY();
            mRot.z = 0.0f;
        } else {
            mRot.x = custom.rotCtrl().getLocalMtxTempRot().x;
            mRot.y = custom.rotCtrl().getLocalMtxTempRot().y;
            mRot.z = custom.rotCtrl().getLocalMtxTempRot().z;
        }
    } else if (obj().model().anim().currentG3DAnimIndex() == 4) {
        Matrix34 mtx = obj().model().model().nodes().at(1).localMtx().rtMtx();
        Vector2 dir = mtx.getVecFront().getXY();
        f32 rotZ = acos(dir.cos(Vector2::BASIS_X * obj().target().getSign()));
        if (dir.y > 0.0f) {
            rotZ *= -1.0f;
        }
        mRot.z = 57.29578f * rotZ;
        mRot.x = custom.rotCtrl().getRotX();
        mRot.y = param.mRotYMax * obj().target().getSign();
    } else {
        mRot.x = custom.rotCtrl().getRotX();
        mRot.y = param.mRotYMax * obj().target().getSign();
        mRot.z = 0.0f;
    }
    custom.rotCtrl().toInvalid();
    obj().model().model().nodes().at(1).localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, mRot.z)) *
                                                  Matrix34::CreateRotXYZDeg(Vector3(mRot.x, 0.0f, 0.0f)) *
                                                  Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRot.y, 0.0f)));
    obj().model().reqScript(4);
}

StateDead::~StateDead() {
    for (u32 i = 0; i < 4; i++) {
        ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromPadChan(i);
        if (hero.isAlive()) {
            hero->stateChecker().setDemo(false);
        }
    }
}

void StateDead::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!mIsStaged) {
        stagingBossDead();
        return;
    }
    if (mIsFirst) {
        mIsFirst = false;
        Utility::DisappearBossPanel(obj());
        if (custom.mahoroaCtrl().getPhase() == 2) {
            custom.mahoroaCtrl().getCustom().reqMotionEscapeWarpOut();
            custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(3));
        } else {
            custom.mahoroaCtrl().getCustom().bodyEffectCtrl().setInvisible();
            custom.mahoroaCtrl().getCustom().bodyEffectCtrl().setVisible(false);
            custom.mahoroaCtrl().getCustom().reqMotionWait();
            custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(0));
        }
        obj().soundSE().normal().start(0x464);
    }
    if (obj().scriptTrigger().get(0)) {
        custom.mahoroaCtrl().getCustom().reqMotionDead();
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(7));
        custom.mahoroaCtrl().getCustom().bodyEffectCtrl().reqAfterImage();
    }
    if (obj().scriptTrigger().get(1)) {
        custom.mahoroaCtrl().getCustom().reqMotionEscapeWarpIn();
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(9));
    }
    if (obj().scriptTrigger().get(2)) {
        custom.mahoroaCtrl().getCustom().reqMotionEscapeWarpOut();
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(10));
    }
    if (obj().scriptTrigger().get(3)) {
        custom.mahoroaCtrl().getCustom().reqMotionWait();
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(8));
        custom.mahoroaCtrl().getCustom().bodyEffectCtrl().reqAfterImage();
    }
    if (obj().scriptTrigger().get(4)) {
        if (Utility::IsArena(obj())) {
            obj().comp().bossManager().arenaCtrl().setNextScene(true);
        } else {
            obj().comp().heroManager().setNextStateLandiaEscape(true);
        }
    }
}

void StateDead::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateDead::procFixPos() {
    const Param& param = obj().param().roah();
    mRot.x = Math::LinearInterpolation(mRot.x, param.mDeadRotX, param.mDeadRotXRate);
    mRot.y = Math::LinearInterpolation(mRot.y, param.mRotYMax * obj().target().getSign(), param.mDeadRotYRate);
    mRot.z = Math::LinearInterpolation(mRot.z, param.mDeadRotZ * obj().target().getSign(), param.mDeadRotZRate);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, mRot.z)) *
                                                  Matrix34::CreateRotXYZDeg(Vector3(mRot.x, 0.0f, 0.0f)) *
                                                  Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRot.y, 0.0f)));
}

void StateDead::stagingBossDead() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!mIsStaged && !Utility::IsHeroDeadStop(obj())) {
        mIsStaged = true;
        obj().model().model().nodes().at(12).setVisibilityBelow(true);
        obj().comp().enemyManager().reqDeadAllEnemyForBoss();
        obj().comp().weaponManager().reqDeadByTeamNoForBoss(static_cast< ::scn::step::ocoll::TeamNo>(1));
        custom.weaponCtrl().requestStarInvisible();
        if (!Utility::IsArena(obj())) {
            obj().comp().heroManager().setHidDisable();
        }
        for (u32 i = 0; i < 4; i++) {
            ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromPadChan(i);
            if (hero.isAlive()) {
                hero->stateChecker().setDemo(true);
            }
        }
        Utility::StagingBossDead(obj(), Vector3(param.mDeadOffset), 0x43D);
        obj().effect().state().releaseAndVanish();
        obj().effect().normal().releaseAndVanish();
        obj().effect().super().releaseAndVanish();
        obj().effect().state().requestN(static_cast<effect::Kind>(0x4C1), 2);
    }
}

}}}}  // namespace scn::step::boss::roah
