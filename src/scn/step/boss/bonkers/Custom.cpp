// TODO: isAlive() is inline in the original; the shared header has its body behind this.
#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/boss/bonkers/Custom.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/VacuumReceiver.h"
#include "scn/step/boss/bonkers/NodeKind.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/common/CollUtil.h"
#include "scn/step/boss/common/Param.h"
#include "scn/step/boss/common/StateAppear.h"
#include "scn/step/boss/common/StateDead.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "std/min.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

Custom::Custom(Boss& boss) : CustomBase(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().bonkers();
    const common::Param& commonParam = obj().param().common();
    const u32 hitPoints[] = { param.mHitPoint[0], param.mHitPoint[1], param.mHitPoint[2] };
    static const u32 maxLevel = 2;
    u32 level = std::min<u32>(maxLevel, obj().level());
    u32 hitPoint;
    if (Utility::IsVariationExtra(obj())) {
        if (obj().isSuper()) {
            hitPoint = hitPoints[level] * commonParam.mExtraHitPointRate * commonParam.mSuperHitPointRate;
        } else {
            hitPoint = hitPoints[level] * commonParam.mExtraHitPointRate;
        }
        obj().hitPoint().init(hitPoint);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRateExtra);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Bonkers.Brain.ExecBossRushEx");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Bonkers.Brain.ExecEx");
            obj().angry().setChangeBrain("Scn.Step.Boss.Bonkers.Brain.ExecAngryEx");
        }
    } else {
        if (obj().isSuper()) {
            hitPoint = hitPoints[level] * commonParam.mSuperHitPointRate;
        } else {
            hitPoint = hitPoints[level];
        }
        obj().hitPoint().init(hitPoint);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRate);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Bonkers.Brain.ExecBossRush");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Bonkers.Brain.Exec");
            obj().angry().setChangeBrain("Scn.Step.Boss.Bonkers.Brain.ExecAngry");
        }
    }
    obj().hitPoint().initDeadBent(commonParam.mDeadBent);
    obj().mapColl().setActorSetting(param._C, param._10, param._14);
    obj().mapColl().setValid(true);
    setBodyCollDefault();
    if (obj().isSuper()) {
        obj().vacuumReceiver().setAbilityKind(hero::ABILITY_KIND_SUPER_HAMMER);
    } else {
        obj().vacuumReceiver().setAbilityKind(hero::ABILITY_KIND_HAMMER);
    }
    obj().stateChanger().setNextState<common::StateAppear, Boss*>(objPtr());
}

void Custom::onAppear() {
    const Param& param = obj().param().bonkers();
    if (obj().isSuper()) {
        obj().effect().super().requestN(static_cast<effect::Kind>(0x2CC), 3);
        obj().effect().super().requestN(effect::KIND_132, 0, hel::math::Vector2(param.mBodyCollOffset).toVector3());
    }
    obj().shadow().setVisibility(true);
}

void Custom::onStart() {
    obj().worldCage().setIsValid(true);
    obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
}

void Custom::onDamage() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
}

void Custom::onDead() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(5));
    obj().stateChanger().setNextState<common::StateDead, Boss*, NodeKind>(objPtr(), NODE_KIND_TOP);
}

void Custom::onProcAnim() {}

void Custom::onProcFixPos() {}

void Custom::setBodyCollDefault() {
    const Param& param = obj().param().bonkers();
    common::CollUtil::SetBodyCollDefault(obj(), 0, param.mBodyCollRadius, param.mBodyCollOffset);
}

void Custom::setBodyCollSwing() {
    const Param& param = obj().param().bonkers();
    chara::BodyColl& bodyColl = obj().objColl().bodyColl();
    bodyColl.clear();
    bodyColl.initAttackType(static_cast<ocoll::AttackType>(0x1AC));
    obj().objColl().addBodyColl(0, param.mBodyCollRadius, param.mBodyCollOffset);
    bodyColl.setResistLv(ocoll::HIT_RESIST_LV_6);
}

void Custom::reqBomb(hel::math::Vector2 pos, hel::math::Vector2 speed, map::BinEnemySize size) {
    enemy::Desc desc(static_cast<map::BinEnemyKind>(0x76), map::BinEnemyVariation_0, 0, static_cast<map::BinEnemyDirType>(0), size, false, false,
                     pos);
    desc._28 = true;
    desc._20 = obj().location().pos().getXY();
    util::ObjRefHandle<enemy::Enemy> bomb = obj().comp().enemyManager().request(desc);
    if (bomb.isAlive()) {
        bomb->move().setVelocity(speed.toVector3());
        bomb->target().setIsRightDir(speed.x > 0.0f);
    }
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::bonkers

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
