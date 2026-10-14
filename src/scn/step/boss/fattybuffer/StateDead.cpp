#include "scn/step/boss/fattybuffer/StateDead.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/ArenaCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/item/ShipPartKind.h"
#include "scn/step/weapon/Manager.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateDead::StateDead(Boss* boss) : StateBase(boss), mIsEnd(false), mIsPanelShown(true), mIsStaged(false) {
    if (obj().objColl().bodyColl().hit().isCollide()) {
        Vector2 attackPos = obj().objColl().bodyColl().damageInfo().attackPos();
        obj().target().setIsRightDir(attackPos.x > obj().location().pos().x);
    }
    obj().hitStop().clear();
    obj().footState().setAir();
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_0);
    stagingBossDead();
    obj().move().resetVelocity();
}

StateDead::~StateDead() {}

void StateDead::procAnim() {
    if (!mIsStaged) {
        stagingBossDead();
        return;
    }
    if (mIsPanelShown) {
        mIsPanelShown = false;
        Utility::DisappearBossPanel(obj());
    }
    if (!mIsEnd && obj().model().isAllEnd()) {
        mIsEnd = true;
        if (Utility::IsArena(obj())) {
            obj().comp().bossManager().arenaCtrl().setNextScene(true);
        } else {
            Utility::GenerateShipParts(obj(), static_cast<item::ShipPartKind>(2),
                                       obj().location().pos() + Vector3(0.0f, 1.75f, 0.0f),
                                       obj().basePos() + Vector2(-3.5f, 2.0f));
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(9));
            obj().effect().state().changeLayer(static_cast<core::DrawLayerKind>(7));
            obj().effect().state().requestP(static_cast<effect::Kind>(0x6C),
                                            obj().location().pos() + Vector3(0.0f, 1.75f, 4.0f));
            obj().soundSE().normal().start(0x363);
            obj().model().setVisibility(false);
            obj().shadow().setVisibility(false);
        }
    }
}

void StateDead::procMove() {
    const Param& param = obj().param().fattybuffer();
    if (obj().footState().isGround()) {
        obj().move().groundDecel(param._14);
    } else {
        obj().move().airDecelFall(param._18, param._1C);
    }
}

void StateDead::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().footState().setGround();
    }
}

void StateDead::stagingBossDead() {
    const Param& param = obj().param().fattybuffer();
    if (!mIsStaged && !Utility::IsHeroDeadStop(obj())) {
        mIsStaged = true;
        obj().comp().enemyManager().reqDeadAllEnemyForBoss();
        obj().comp().weaponManager().reqDeadByTeamNo(static_cast<ocoll::TeamNo>(1));
        obj().model().reqScript(4);
        Utility::StagingBossDead(obj(), param._1B4);
        obj().effect().state().releaseAndVanish();
        obj().effect().normal().releaseAndVanish();
    }
}

}}}}  // namespace scn::step::boss::fattybuffer
