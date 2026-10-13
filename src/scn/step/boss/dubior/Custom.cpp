#include "scn/step/boss/dubior/Custom.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "mcoll/LandManager.h"
#include "mcoll/detail/DetectArg.h"
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
#include "scn/step/boss/dubior/NodeKind.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateWait.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/debug/GeneralDrawer.h"
#include "scn/step/map/LandManager.h"
#include "std/min.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

Custom::Custom(Boss& boss) : CustomBase(boss), mEnemyCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().dubior();
    const common::Param& commonParam = obj().param().common();
    const u32 hitPoints[] = { param.mHitPoint[0], param.mHitPoint[1], param.mHitPoint[2] };
    static const u32 maxLevel = 2;
    u32 level = std::min<u32>(maxLevel, obj().level());
    if (Utility::IsVariationExtra(obj())) {
        obj().hitPoint().init(hitPoints[level] * commonParam.mExtraHitPointRate);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRateExtra);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Dubior.Brain.ExecBossRushEx");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Dubior.Brain.ExecEx");
            obj().angry().setChangeBrain("Scn.Step.Boss.Dubior.Brain.ExecAngryEx");
        }
    } else {
        obj().hitPoint().init(hitPoints[level]);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRate);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Dubior.Brain.ExecBossRush");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Dubior.Brain.Exec");
            obj().angry().setChangeBrain("Scn.Step.Boss.Dubior.Brain.ExecAngry");
        }
    }
    obj().hitPoint().initDeadBent(commonParam.mDeadBent);
    obj().mapColl().setActorSetting(param._C, param._10, param._14);
    obj().mapColl().setValid(true);
    setBodyCollDefault();
    obj().vacuumReceiver().setAbilityKind(hero::ABILITY_KIND_SPARK);
    obj().stateChanger().setNextState<common::StateAppear, Boss*>(objPtr());
}

void Custom::onAppear() {
    obj().shadow().setVisibility(true);
}

void Custom::onStart() {
    obj().worldCage().setIsValid(true);
    obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
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

hel::math::Vector2 Custom::getFirstOffs() const {
    const Param& param = obj().param().dubior();
    return hel::math::Vector2(0.0f, param.mFirstOffsY);
}

void Custom::setBodyCollDefault() {
    const Param& param = obj().param().dubior();
    common::CollUtil::SetBodyCollDefault(obj(), 0, param.mBodyCollRadius, param.mBodyCollOffset, param.mBodyCollOffset2);
}

void Custom::setBodyCollFastMove() {
    const Param& param = obj().param().dubior();
    chara::BodyColl& bodyColl = obj().objColl().bodyColl();
    bodyColl.clear();
    bodyColl.initAttackType(static_cast<ocoll::AttackType>(0x1AB));
    obj().objColl().addBodyColl(0, param.mFastMoveCollRadius, param.mFastMoveCollOffset);
    bodyColl.setResistLv(ocoll::HIT_RESIST_LV_2);
}

void Custom::setBodyCollDash() {
    const Param& param = obj().param().dubior();
    chara::BodyColl& bodyColl = obj().objColl().bodyColl();
    bodyColl.clear();
    bodyColl.initAttackType(static_cast<ocoll::AttackType>(0x1B0));
    obj().objColl().addBodyColl(0, param.mDashCollRadius, param.mDashCollOffset, param.mDashCollOffset2);
    bodyColl.setResistLv(ocoll::HIT_RESIST_LV_2);
}

void Custom::reqThunderGroundEffect() {
    hel::math::Vector2 pos = obj().location().pos().getXY();
    hel::math::Vector2 step = hel::math::Vector2::BASIS_Y * -0.1f;
    u32 i = 0;
    while (++i < 100) {
        obj().comp().debugGeneralDrawer().addArrow(pos, pos + step);
        mcoll::detail::DetectResult result = detect(pos, step);
        pos += step;
        bool isHit = false;
        for (u32 j = 0; j < result.collidedLogCount(); j++) {
            mcoll::detail::CollidedLog log = result.collidedLog(j);
            if (log.isValid() && log.info().isValid() && log.info().collideTarget().isValid()) {
                obj().effect().normal().requestP(static_cast<effect::Kind>(0x4F1), (pos + step).toVector3());
                if (log.info().collideTarget()._5 == 0) {
                    isHit = true;
                    break;
                }
            }
        }
        if (isHit) {
            break;
        }
    }
}

mcoll::detail::DetectResult Custom::detect(const hel::math::Vector2& pos, const hel::math::Vector2& move) {
    mcoll::detail::DetectArg arg;
    arg.setVelocity(move);
    return obj().comp().mapLandManager().native().rayCheck(pos, arg);
}

EnemyCtrl& Custom::enemyCtrl() {
    return mEnemyCtrl;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::dubior

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
