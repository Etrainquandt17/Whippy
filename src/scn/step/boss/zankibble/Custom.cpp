#include "scn/step/boss/zankibble/Custom.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/VacuumReceiver.h"
#include "scn/step/boss/common/CollUtil.h"
#include "scn/step/boss/common/Param.h"
#include "scn/step/boss/common/StateAppear.h"
#include "scn/step/boss/common/StateDead.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/zankibble/NodeKind.h"
#include "scn/step/boss/zankibble/Param.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "std/min.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

Custom::Custom(Boss& boss) : CustomBase(boss), mEnemyCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().zankibble();
    const common::Param& commonParam = obj().param().common();
    const u32 hitPoints[] = { param.mHitPoint[0], param.mHitPoint[1], param.mHitPoint[2] };
    static const u32 maxLevel = 2;
    u32 level = std::min<u32>(maxLevel, obj().level());
    if (Utility::IsVariationExtra(obj())) {
        obj().hitPoint().init(hitPoints[level] * commonParam.mExtraHitPointRate);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRateExtra);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Zankibble.Brain.ExecBossRushEx");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Zankibble.Brain.ExecEx");
            obj().angry().setChangeBrain("Scn.Step.Boss.Zankibble.Brain.ExecAngryEx");
        }
    } else {
        obj().hitPoint().init(hitPoints[level]);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRate);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Zankibble.Brain.ExecBossRush");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Zankibble.Brain.Exec");
            obj().angry().setChangeBrain("Scn.Step.Boss.Zankibble.Brain.ExecAngry");
        }
    }
    obj().hitPoint().initDeadBent(commonParam.mDeadBent);
    obj().mapColl().setActorSetting(param._C, param._10, param._14);
    obj().mapColl().setValid(true);
    common::CollUtil::SetBodyCollDefault(obj(), 0, param.mBodyCollRadius, param.mBodyCollOffset);
    obj().vacuumReceiver().setAbilityKind(hero::ABILITY_KIND_CUTTER);
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

EnemyCtrl& Custom::enemyCtrl() {
    return mEnemyCtrl;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::zankibble

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
