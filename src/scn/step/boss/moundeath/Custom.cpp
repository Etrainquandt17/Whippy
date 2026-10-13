#include "scn/step/boss/moundeath/Custom.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/VacuumReceiver.h"
#include "scn/step/boss/common/CollUtil.h"
#include "scn/step/boss/common/Param.h"
#include "scn/step/boss/common/StateAppear.h"
#include "scn/step/boss/common/StateDead.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/moundeath/NodeKind.h"
#include "scn/step/boss/moundeath/Param.h"
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
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "std/min.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

Custom::Custom(Boss& boss) : CustomBase(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().moundeath();
    const common::Param& commonParam = obj().param().common();
    const u32 hitPoints[] = { param.mHitPoint[0], param.mHitPoint[1], param.mHitPoint[2] };
    static const u32 maxLevel = 2;
    u32 level = std::min<u32>(maxLevel, obj().level());
    if (Utility::IsVariationExtra(obj())) {
        obj().hitPoint().init(hitPoints[level] * commonParam.mExtraHitPointRate);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRateExtra);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Moundeath.Brain.ExecBossRushEx");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Moundeath.Brain.ExecEx");
            obj().angry().setChangeBrain("Scn.Step.Boss.Moundeath.Brain.ExecAngryEx");
        }
    } else {
        obj().hitPoint().init(hitPoints[level]);
        obj().angry().setAngryHpRate(commonParam.mAngryHpRate);
        if (Utility::IsVariationBossRush(obj())) {
            obj().brainCtrl().set("Scn.Step.Boss.Moundeath.Brain.ExecBossRush");
        } else {
            obj().brainCtrl().set("Scn.Step.Boss.Moundeath.Brain.Exec");
            obj().angry().setChangeBrain("Scn.Step.Boss.Moundeath.Brain.ExecAngry");
        }
    }
    obj().hitPoint().initDeadBent(commonParam.mDeadBent);
    obj().mapColl().setActorSetting(param._C, param._10, param._14);
    obj().mapColl().setValid(true);
    setBodyCollDefault();
    obj().vacuumReceiver().setAbilityKind(static_cast<hero::AbilityKind>(9));
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
    obj().stateChanger().setNextState<common::StateDead, Boss*, NodeKind>(objPtr(), NODE_KIND_0);
}

void Custom::onProcAnim() {}

void Custom::onProcFixPos() {}

void Custom::setBodyCollDefault() {
    const Param& param = obj().param().moundeath();
    common::CollUtil::SetBodyCollDefault(obj(), 0, param.mBodyCollRadius, param.mBodyCollOffset);
}

void Custom::setBodyCollRolling() {
    const Param& param = obj().param().moundeath();
    chara::BodyColl& bodyColl = obj().objColl().bodyColl();
    bodyColl.clear();
    bodyColl.initAttackType(static_cast<ocoll::AttackType>(0x1B5));
    obj().objColl().addBodyColl(0, param.mBodyCollRadius, param.mBodyCollOffset);
    bodyColl.setResistLv(ocoll::HIT_RESIST_LV_6);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::moundeath

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
