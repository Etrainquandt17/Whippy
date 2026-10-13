#include "scn/step/boss/gigantedge/Custom.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Math.h"
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
#include "scn/step/boss/common/CollUtil.h"
#include "scn/step/boss/common/Param.h"
#include "scn/step/boss/common/StateAppear.h"
#include "scn/step/boss/common/StateDead.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/gigantedge/NodeKind.h"
#include "scn/step/boss/gigantedge/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "std/min.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

Custom::Custom(Boss& boss) : CustomBase(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().gigantedge();
    const common::Param& commonParam = obj().param().common();
    const u32 hitPoints[] = { param.mHitPoint[0], param.mHitPoint[1], param.mHitPoint[2] };
    static const u32 maxLevel = 2;
    u32 level = std::min<u32>(maxLevel, obj().level());
    if (Utility::IsVariationExtra(obj())) {
        obj().hitPoint().init(hitPoints[level] * commonParam.mExtraHitPointRate);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRateExtra);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.GigantEdge.Brain.ExecBossRushEx");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.GigantEdge.Brain.ExecEx");
            obj().angry().setChangeBrain("Scn.Step.Boss.GigantEdge.Brain.ExecAngryEx");
        }
    } else {
        obj().hitPoint().init(hitPoints[level]);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRate);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.GigantEdge.Brain.ExecBossRush");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.GigantEdge.Brain.Exec");
            obj().angry().setChangeBrain("Scn.Step.Boss.GigantEdge.Brain.ExecAngry");
        }
    }
    obj().hitPoint().initDeadBent(commonParam.mDeadBent);
    obj().mapColl().setActorSetting(param._C, param._10, param._14);
    obj().mapColl().setValid(true);
    common::CollUtil::SetBodyCollDefault(obj(), 0, param.mBodyCollRadius, param.mBodyCollOffset);
    obj().vacuumReceiver().setAbilityKind(hero::ABILITY_KIND_SWORD);
    obj().stateChanger().setNextState<common::StateAppear, Boss*>(objPtr());
}

void Custom::onAppear() {
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

void Custom::setBodyCollGuard() {
    chara::BodyColl& bodyColl = obj().objColl().bodyColl();
    const Param& param = obj().param().gigantedge();
    bodyColl.clear();
    bodyColl.initAttackType(static_cast<ocoll::AttackType>(0x1AB));
    obj().objColl().addBodyColl(0, param.mBodyCollRadius, param.mBodyCollOffset);
    hel::math::Vector2 offset = param.mGuardCollOffset;
    offset.x *= obj().target().getSign();
    hel::math::Vector2 offset2 = param.mGuardCollOffset2;
    offset2.x *= obj().target().getSign();
    obj().objColl().addBodyColl(3, param.mGuardCollRadius, offset, offset2);
    bodyColl.setResistLv(ocoll::HIT_RESIST_LV_6);
}

void Custom::reqSwordShot(bool isTriple) {
    const Param& param = obj().param().gigantedge();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    hel::math::Vector2 offset(param.mSwordShotOffset.x * obj().target().getSign(), param.mSwordShotOffset.y);
    u32 num = isTriple ? 3 : 1;
    u32 i = 0;
    if (num != 0) {
        for (; i < num; i++) {
            hel::math::Vector2 speed = hel::math::Vector2::BASIS_X * obj().target().getSign();
            speed.rotate(i * hel::math::Math::DegToRad(param.mSwordShotAngle * obj().target().getSign()));
            speed.normalize();
            speed *= param.mSwordShotSpeed;
            // TODO: the original keeps the address of this sum in a saved register, loaded ahead of the loop (one instruction
            // more); everything else is the same.
            weapon::Desc desc(static_cast<weapon::Kind>(0x2C), isTriple, static_cast<ostop::Flag>(8), pos + offset, speed, obj().objColl().owner());
            util::ObjRefHandle<weapon::Weapon> shot = obj().comp().weaponManager().request(desc);
        }
    }
    obj().effect().normal().requestP(static_cast<effect::Kind>(0x531), obj().location().pos() + offset.toVector3());
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::gigantedge

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
