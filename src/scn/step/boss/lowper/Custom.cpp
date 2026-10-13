#include "scn/step/boss/lowper/Custom.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/EnergySphereCtrl.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/StateCallback.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/BackEffectCtrl.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateDead.h"
#include "scn/step/boss/lowper/StateFirst.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
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
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "std/min.h"
#include "util/ObjList.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

Custom::Custom(Boss& boss)
    : CustomBase(boss), mCollisionCtrl(boss), mDataBuff(), mEnemyCtrl(boss), mGearCtrl(boss), mItemCtrl(boss), mWaftMoveCtrl(boss),
      mMiniBlackHoleCtrl(boss), mBackEffectCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().lowper();
    const u32 hitPoints[] = { param._0, param._4, param._8, param._C };
    static const u32 maxLevel = 3;
    obj().hitPoint().init(hitPoints[std::min<u32>(maxLevel, obj().level())]);
    obj().angry().setAngryHpRate(param._10);
    if (Utility::IsVariationExtra(obj())) {
        obj().brainCtrl().set("Scn.Step.Boss.Lowper.Brain.Brain.ExecEx");
        obj().angry().setChangeBrain("Scn.Step.Boss.Lowper.Brain.Brain.ExecAngryEx");
    } else {
        obj().brainCtrl().set("Scn.Step.Boss.Lowper.Brain.Brain.Exec");
        obj().angry().setChangeBrain("Scn.Step.Boss.Lowper.Brain.Brain.ExecAngry");
    }
    obj().model().rotCtrl().setRotHTargetDefault(30.0f);
    obj().model().rotCtrl().initRotH(0.0f);
    obj().model().anim().subAnimSet(0, 3, 1);
    obj().model().anim().subAnimAccessor(0).start(true);
    switch (obj().level()) {
    case 0:
        obj().model().model().nodes().at(4).setVisibility(false);
        obj().model().model().nodes().at(7).setVisibility(false);
        obj().model().model().nodes().at(8).setVisibility(false);
        break;
    case 1:
        obj().model().model().nodes().at(5).setVisibility(false);
        obj().model().model().nodes().at(6).setVisibility(false);
        break;
    case 2:
        obj().model().model().nodes().at(4).setVisibility(false);
        break;
    }
    obj().stateCallback().setCanClearAttack(false);
    obj().stateChanger().setNextState<StateFirst, Boss*>(objPtr());
}

void Custom::onAppear() {}

void Custom::onStart() {
    obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
}

void Custom::onDamage() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
    obj().soundSE().normal().start(0x564);
}

void Custom::onDead() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(5));
    mMiniBlackHoleCtrl.clear();
    mBackEffectCtrl.onDead();
    obj().stateChanger().setNextState<StateDead, Boss*>(objPtr());
}

void Custom::onProcAnim() {
    mEnemyCtrl.update();
    mItemCtrl.update();
    mMiniBlackHoleCtrl.update();
    mBackEffectCtrl.update();
}

void Custom::onProcMove() {
    mWaftMoveCtrl.update();
}

void Custom::onProcFixPos() {
    obj().angry().check();
    mCollisionCtrl.update();
    obj().comp().bossManager().energySphereCtrl().setConstraintPos(obj().location().pos());
}

CollisionCtrl& Custom::collisionCtrl() {
    return mCollisionCtrl;
}

DataBuff& Custom::dataBuff() {
    return mDataBuff;
}

EnemyCtrl& Custom::enemyCtrl() {
    return mEnemyCtrl;
}

GearCtrl& Custom::gearCtrl() {
    return mGearCtrl;
}

ItemCtrl& Custom::itemCtrl() {
    return mItemCtrl;
}

WaftMoveCtrl& Custom::waftMoveCtrl() {
    return mWaftMoveCtrl;
}

MiniBlackHoleCtrl& Custom::miniBlackHoleCtrl() {
    return mMiniBlackHoleCtrl;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::lowper

namespace g3d {

class Model;

}  // namespace g3d

template util::ObjListNode<g3d::Model, util::ObjListDummyType>::~ObjListNode();

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
