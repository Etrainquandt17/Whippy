#include "scn/step/boss/doubter/Custom.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Handicap.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateCallback.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateDamageL.h"
#include "scn/step/boss/doubter/StateDead.h"
#include "scn/step/boss/doubter/StateFirst.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/Shake.h"
#include "util/ObjList.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

Custom::Custom(Boss& boss)
    : CustomBase(boss), mBodyCollCtrl(boss), mCaptureCtrl(boss), mJugglingCtrl(boss), mPunchCtrlR(boss, NODE_KIND_2, -1.0f),
      mPunchCtrlL(boss, NODE_KIND_3, 1.0f), mWaftPositionCtrl(boss) {}

void Custom::onInit() {
    const Param& param = obj().param().doubter();
    obj().hitPoint().init(Utility::IsVariationExtra(obj()) ? param.mHitPointExtra : param.mHitPoint);
    obj().angry().setAngryHpRate(Utility::IsVariationExtra(obj()) ? param.mAngryHpRateExtra : param.mAngryHpRate);
    obj().handicap().setup();
    obj().target().setIsRightDir(false);
    obj().mapColl().setActorSetting(1.4f, 0.49f, 0.99f);
    obj().mapColl().setValid(true);
    obj().shadow().changeDiameter(2.0f);
    obj().shadow().changeMaxHeight(12.0f);
    obj().shadow().setVisibility(true);
    if (Utility::IsVariationExtra(obj())) {
        obj().brainCtrl().set("Scn.Step.Boss.Doubter.Brain.ExecEx");
        obj().angry().setChangeBrain("Scn.Step.Boss.Doubter.Brain.ExecAngryEx");
    } else {
        obj().brainCtrl().set("Scn.Step.Boss.Doubter.Brain.Exec");
        obj().angry().setChangeBrain("Scn.Step.Boss.Doubter.Brain.ExecAngry");
    }
    obj().stateCallback().setCanClearAttack(false);
    obj().stateChanger().setNextState<StateFirst, Boss*>(objPtr());
}

void Custom::onAppear() {}

void Custom::onStart() {}

void Custom::onDamage() {
    obj().model().shake().request(static_cast<chara::ShakeKind>(4));
}

void Custom::onDead() {
    mCaptureCtrl.release();
    mPunchCtrlR.deadEnd();
    mPunchCtrlL.deadEnd();
    obj().stateChanger().setNextState<StateDead, Boss*>(objPtr());
}

void Custom::onStateChange() {
    mBodyCollCtrl.onStateChange();
}

void Custom::onProcAnim() {
    mJugglingCtrl.update();
    mPunchCtrlR.update();
    mPunchCtrlL.update();
    mCaptureCtrl.update();
    mWaftPositionCtrl.update();
}

void Custom::onProcFixPos() {
    if (obj().angry().check()) {
        obj().stateChanger().setNextState<StateDamageL, Boss*>(objPtr());
        obj().stateChanger().changeStateIfPossible();
    }
}

BodyCollCtrl& Custom::bodyCollCtrl() {
    return mBodyCollCtrl;
}

CaptureCtrl& Custom::captureCtrl() {
    return mCaptureCtrl;
}

JugglingCtrl& Custom::jugglingCtrl() {
    return mJugglingCtrl;
}

PunchCtrl& Custom::punchCtrlR() {
    return mPunchCtrlR;
}

PunchCtrl& Custom::punchCtrlL() {
    return mPunchCtrlL;
}

WaftPositionCtrl& Custom::waftPositionCtrl() {
    return mWaftPositionCtrl;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::boss::doubter

namespace g3d {

class Model;

}  // namespace g3d

template util::ObjListNode<g3d::Model, util::ObjListDummyType>::~ObjListNode();

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();
