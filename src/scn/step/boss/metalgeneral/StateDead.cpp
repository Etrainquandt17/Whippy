#include "scn/step/boss/metalgeneral/StateDead.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/ArenaCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Gear.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/CollisionCtrl.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/ScriptKind.h"
#include "scn/step/boss/metalgeneral/StateAnger.h"
#include "scn/step/boss/metalgeneral/StateCircling.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlight.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlightEnd.h"
#include "scn/step/boss/metalgeneral/StateDamageL.h"
#include "scn/step/boss/metalgeneral/StateDeadJump.h"
#include "scn/step/boss/metalgeneral/StateFall.h"
#include "scn/step/boss/metalgeneral/StateFirst.h"
#include "scn/step/boss/metalgeneral/StateLanding.h"
#include "scn/step/boss/metalgeneral/StatePatriotClimb.h"
#include "scn/step/boss/metalgeneral/StatePatriotFall.h"
#include "scn/step/boss/metalgeneral/StatePatriotLaunch.h"
#include "scn/step/boss/metalgeneral/StatePatriotMoveToFar.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackle.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackleLower.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackleUpper.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/boss/metalgeneral/States.h"
#include "scn/step/boss/metalgeneral/WeaponCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/carryitem/Manager.h"
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
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/weapon/Manager.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateDead::StateDead(Boss* boss)
    : StateBase(boss), mIsEnd(false), mIsPanelShown(true), mIsStaged(false), mFrame(0), mZoomHandle(0), _14(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().hitStop().clear();
    obj().footState().setAir();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    obj().move().resetVelocity();
    if (obj().objColl().bodyColl().hit().isCollide()) {
        Vector2 attackPos = obj().objColl().bodyColl().damageInfo().attackPos();
        obj().target().setIsRightDir(attackPos.x > obj().location().pos().x);
    }
    stagingBossDead();
    obj().mapColl().setValid(true);
}

StateDead::~StateDead() {}

void StateDead::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (!mIsStaged) {
        stagingBossDead();
        return;
    }
    if (mIsPanelShown) {
        mIsPanelShown = false;
        Utility::DisappearBossPanel(obj());
        if (!Utility::IsArena(obj())) {
            obj().comp().carryItemManager().killAllObj();
        }
    }
    if (mIsEnd) {
        mFrame++;
        if (mFrame == param._2CC && !Utility::IsArena(obj())) {
            obj().comp().heroManager().setNextStateClearDance();
        }
        return;
    }
    if (obj().model().isAllEnd()) {
        mIsEnd = true;
        if (Utility::IsArena(obj())) {
            obj().comp().bossManager().arenaCtrl().setNextScene(true);
        } else {
            _14 = param._2D0;
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(9));
            obj().effect().normal().release();
            obj().effect().state().changeLayer(static_cast<core::DrawLayerKind>(7));
            obj().effect().state().requestP(static_cast<effect::Kind>(0x6C),
                                            obj().location().pos() + Vector3(param._2C0));
            obj().soundSE().normal().start(0x30E);
            obj().model().setVisibility(false);
            obj().shadow().setVisibility(false);
        }
    }
}

void StateDead::procMove() {
    const Param& param = obj().param().metalgeneral();
    if (obj().footState().isGround()) {
        obj().move().groundDecel(param._1C);
    } else {
        obj().move().airDecelFall(param._20, param._24);
    }
}

void StateDead::procFixPos() {
    const Param& param = obj().param().metalgeneral();
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().footState().setGround();
    }
    if (!Utility::IsArena(obj()) && mFrame < param._2CC) {
        u32 count = obj().comp().heroManager().getPlayerCount();
        for (u32 i = 0; i < count; i++) {
            if (static_cast<const hero::Hero&>(obj().comp().heroManager().getPlayerByIndex(i)).location().pos().x <
                obj().location().pos().x) {
                obj().comp().heroManager().getPlayerByIndex(i).target().setIsRightDir(true);
            } else {
                obj().comp().heroManager().getPlayerByIndex(i).target().setIsRightDir(false);
            }
        }
    }
}

void StateDead::stagingBossDead() {
    const Param& param = obj().param().metalgeneral();
    if (!mIsStaged && !Utility::IsHeroDeadStop(obj())) {
        mIsStaged = true;
        if (!Utility::IsArena(obj())) {
            Utility::DoNotMovePlayerWhenClear(obj());
        } else {
            obj().comp().enemyManager().reqDeadAllEnemyForBoss();
            obj().comp().weaponManager().reqDeadByTeamNo(static_cast<ocoll::TeamNo>(1));
        }
        obj().model().reqScript(4);
        obj().gearManager().gear(0).setVisibility(false);
        Utility::StagingBossDead(obj(), param._2C0);
        if (!Utility::IsArena(obj())) {
            setCameraZoom();
        }
    }
}

void StateDead::setCameraZoom() {
    const Param& param = obj().param().metalgeneral();
    f32 height = param._88 - param._8C;
    Vector2 center;
    center.x = obj().location().pos().x;
    center.y = 0.5f * (param._88 + param._8C) + obj().basePos().y;
    mZoomHandle = obj().comp().cameraController().setZoom(center, height);
}

}}}}  // namespace scn::step::boss::metalgeneral
