#include "scn/step/boss/whispy/Custom.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Handicap.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/boss/whispy/StateDamageL.h"
#include "scn/step/boss/whispy/StateDead.h"
#include "scn/step/boss/whispy/StateFirst.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

Custom::Custom(Boss& boss)
    : CustomBase(boss), mCaptureCtrl(boss), mDamageEyeCtrl(boss), mEnemyReqBuff(), mEnemyCtrl(boss), mFaceRotCtrl(boss), mTSCtrl(boss),
      mWindCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().whispy();
    if (Utility::IsVariationExtra(obj())) {
        obj().hitPoint().init(param.mHitPointExtra);
        obj().angry().setAngryHpRate(param.mAngryHpRateExtra);
    } else {
        obj().hitPoint().init(param.mHitPoint);
        obj().angry().setAngryHpRate(param.mAngryHpRate);
    }
    obj().handicap().setup();
    obj().target().setIsRightDir(false);
    obj().model().rotCtrl().setRotHTargetDefault(90.0f);
    obj().model().rotCtrl().initRotH(90.0f);
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x197));
    obj().objColl().bodyColl().setStateHitOnly();
    obj().objColl().addBodyColl(0, param.mBodyCollRadius, param.mBodyCollOffset, param.mBodyCollOffset2);
    obj().objColl().bodyColl().setResistLv(ocoll::HIT_RESIST_LV_3);
    if (Utility::IsVariationExtra(obj())) {
        obj().brainCtrl().set("Scn.Step.Boss.Whispy.Brain.ExecEx");
        obj().angry().setChangeBrain("Scn.Step.Boss.Whispy.Brain.ExecAngryEx");
    } else {
        obj().brainCtrl().set("Scn.Step.Boss.Whispy.Brain.Exec");
        obj().angry().setChangeBrain("Scn.Step.Boss.Whispy.Brain.ExecAngry");
    }
    obj().stateChanger().setNextState<StateFirst, Boss*>(objPtr());
}

void Custom::onAppear() {}

void Custom::onStart() {}

void Custom::onDamage() {
    obj().hitStop().clear();
    effect::Kind kind;
    if (Utility::IsVariationExtra(obj())) {
        if (obj().angry().isAngry()) {
            kind = static_cast<effect::Kind>(0x591);
        } else {
            kind = static_cast<effect::Kind>(0x592);
        }
    } else {
        kind = obj().angry().isAngry() ? static_cast<effect::Kind>(0x595) : static_cast<effect::Kind>(0x596);
    }
    obj().effect().normal().requestN(kind, 0);
    mDamageEyeCtrl.set();
}

void Custom::onDead() {
    mCaptureCtrl.release();
    obj().stateChanger().setNextState<StateDead, Boss*>(objPtr());
}

void Custom::onScriptRequested() {
    mFaceRotCtrl.reset();
}

void Custom::onProcAnim() {
    mDamageEyeCtrl.update();
    mWindCtrl.update();
}

void Custom::onProcFixPos() {
    if (obj().angry().check()) {
        obj().stateChanger().setNextState<StateDamageL, Boss*>(objPtr());
        obj().stateChanger().changeStateIfPossible();
    }
}

CaptureCtrl& Custom::captureCtrl() {
    return mCaptureCtrl;
}

DamageEyeCtrl& Custom::damageEyeCtrl() {
    return mDamageEyeCtrl;
}

EnemyReqBuff& Custom::enemyReqBuff() {
    return mEnemyReqBuff;
}

EnemyCtrl& Custom::enemyCtrl() {
    return mEnemyCtrl;
}

FaceRotCtrl& Custom::faceRotCtrl() {
    return mFaceRotCtrl;
}

TSCtrl& Custom::tsctrl() {
    return mTSCtrl;
}

WindCtrl& Custom::windCtrl() {
    return mWindCtrl;
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
