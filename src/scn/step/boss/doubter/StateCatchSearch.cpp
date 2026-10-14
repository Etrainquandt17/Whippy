#include "scn/step/boss/doubter/StateCatchSearch.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/CaptureCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/PunchCtrl.h"
#include "scn/step/boss/doubter/StateCatch.h"
#include "scn/step/boss/doubter/WaftPositionCtrl.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateCatchSearch::StateCatchSearch(Boss* boss, u32 frame, u32 endFrame)
    : StateBase(boss), mCount(frame + endFrame), mEndCount(endFrame), mDecel(boss->param().doubter().mPunch._4), mIsCheckCapture(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x12);
    custom.bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().guard().setType(static_cast<GuardType>(5));
    custom.punchCtrlR().catchSearchStart();
}

StateCatchSearch::~StateCatchSearch() {}

void StateCatchSearch::procAnim() {
    const PunchParam& punch = Utility::IsVariationExtra(obj()) ? obj().param().doubter().mPunchExtra : obj().param().doubter().mPunch;
    if (mCount != 0) {
        mCount--;
        if (mCount == 0) {
            obj().stateChanger().setNextState<StateCatch, Boss*>(objPtr());
            return;
        }
        if (mCount == mEndCount) {
            DynamicCastToRef<Custom, ICustom>(obj().custom()).punchCtrlR().catchSearchEnd();
        }
    }
    if (obj().scriptTrigger().get(2)) {
        obj().move().setSpeedH(punch._8 * obj().target().getSign());
        mDecel = punch._C;
    }
    if (obj().scriptTrigger().get(1)) {
        mIsCheckCapture = true;
    }
}

void StateCatchSearch::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(mDecel));
}

void StateCatchSearch::procFixPos() {}

void StateCatchSearch::procObjCollReact() {
    if (mIsCheckCapture) {
        if (DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().checkCapture()) {
            obj().stateChanger().setNextState<StateCatch, Boss*>(objPtr());
        }
    }
}

}}}}  // namespace scn::step::boss::doubter
