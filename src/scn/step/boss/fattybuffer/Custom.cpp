#include "scn/step/boss/fattybuffer/Custom.h"

#include "g3d/ModelAnimAccessor.h"
#include "gobj/Anim.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Handicap.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateDamageL.h"
#include "scn/step/boss/fattybuffer/StateDead.h"
#include "scn/step/boss/fattybuffer/StateFirst.h"
#include "scn/step/boss/fattybuffer/StateWait.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

Custom::Custom(Boss& boss)
    : CustomBase(boss), mCollisionCtrl(boss), mMapCollCtrl(boss), mEnemyReqBuff(), mEyeCtrl(boss), mPostureCtrl(boss), mStalactiteCtrl(boss),
      mCannonCaptureCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().fattybuffer();
    obj().hitPoint().init(Utility::IsVariationExtra(obj()) ? param.mHitPointExtra : param.mHitPoint);
    obj().angry().setAngryHpRate(Utility::IsVariationExtra(obj()) ? param.mAngryHpRateExtra : param.mAngryHpRate);
    obj().handicap().setup();
    setSubAnimEyeNormal();
    obj().target().setIsRightDir(false);
    mMapCollCtrl.setDefault();
    obj().mapColl().setValid(true);
    obj().shadow().changeDiameter(3.0f);
    obj().shadow().changeMaxHeight(12.0f);
    obj().shadow().setVisibility(true);
    if (Utility::IsVariationExtra(obj())) {
        obj().brainCtrl().set("Scn.Step.Boss.FattyBuffer.Brain.ExecEx");
        obj().angry().setChangeBrain("Scn.Step.Boss.FattyBuffer.Brain.ExecAngryEx");
    } else {
        obj().brainCtrl().set("Scn.Step.Boss.FattyBuffer.Brain.Exec");
        obj().angry().setChangeBrain("Scn.Step.Boss.FattyBuffer.Brain.ExecAngry");
    }
    obj().model().setScale(hel::math::Vector3::ALL_ONE * param.mScaleDefault);
    obj().worldCage().changePadding(1.75f, 0.0f);
    obj().stateChanger().setNextState<StateFirst, Boss*>(objPtr());
}

void Custom::onAppear() {}

void Custom::onStart() {
    obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
}

void Custom::onDamage() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
}

void Custom::onDead() {
    mPostureCtrl.resetTarget();
    obj().stateChanger().setNextState<StateDead, Boss*>(objPtr());
}

void Custom::onProcAnim() {
    mPostureCtrl.update();
    mEyeCtrl.update();
    mCollisionCtrl.update();
}

void Custom::onProcFixPos() {
    if (obj().angry().check()) {
        obj().stateChanger().setNextState<StateDamageL, Boss*>(objPtr());
        obj().stateChanger().changeStateIfPossible();
    }
}

void Custom::setSubAnimEyeNormal() {
    obj().model().anim().subAnimSet(0, 0x29, 8);
    obj().model().anim().subAnimAccessor(0).start(true);
}

void Custom::setSubAnimEyeAngry() {
    obj().model().anim().subAnimSet(0, 0x2A, 8);
    obj().model().anim().subAnimAccessor(0).start(true);
}

CollisionCtrl& Custom::collisionCtrl() {
    return mCollisionCtrl;
}

MapCollCtrl& Custom::mapCollCtrl() {
    return mMapCollCtrl;
}

EnemyReqBuff& Custom::enemyReqBuff() {
    return mEnemyReqBuff;
}

PostureCtrl& Custom::postureCtrl() {
    return mPostureCtrl;
}

StalactiteCtrl& Custom::stalactiteCtrl() {
    return mStalactiteCtrl;
}

CannonCaptureCtrl& Custom::cannonCaptureCtrl() {
    return mCannonCaptureCtrl;
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
