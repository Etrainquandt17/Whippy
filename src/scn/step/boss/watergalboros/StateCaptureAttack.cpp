#include "scn/step/boss/watergalboros/StateCaptureAttack.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/watergalboros/Custom.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/boss/watergalboros/StateCapture.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

StateCaptureAttack::StateCaptureAttack(Boss* boss) : StateBase(boss), mCount(0), mIsCapture(false), mIsSearch(false) {
    obj().model().reqScript(0x11);
    Utility::ControlHateOnAction(obj());
}

StateCaptureAttack::~StateCaptureAttack() {
    obj().objColl().clearSearchHit();
}

void StateCaptureAttack::procAnim() {
    const Param& param = obj().param().watergalboros();
    if (mCount < param.mCaptureAttackFrame) {
        mCount++;
    } else {
        if (mIsCapture) {
            obj().stateChanger().setNextState<StateCapture, Boss*>(objPtr());
        } else {
            obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
        }
        return;
    }
    if (mIsSearch) {
        f32 speed = param.mCaptureAttackSpeed * obj().target().getSign();
        obj().move().setSpeedH(speed);
        mIsSearch = false;
    }
    if (obj().scriptTrigger().get(0)) {
        Vector2 offset;
        offset.x = param.mCaptureSearchOffset.x * obj().target().getSign();
        offset.y = param.mCaptureSearchOffset.y;
        Vector2 offset2;
        offset2.x = param.mCaptureSearchOffset2.x * obj().target().getSign();
        offset2.y = param.mCaptureSearchOffset2.y;
        obj().objColl().addSearchHit(0, param.mCaptureSearchRadius, offset, offset2);
        mIsSearch = true;
    }
    if (obj().scriptTrigger().get(1)) {
        obj().objColl().clearSearchHit();
    }
}

void StateCaptureAttack::procMove() {
    const Param& param = obj().param().watergalboros();
    obj().move().groundDecel(param._24);
}

void StateCaptureAttack::procObjCollReact() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.captureCtrl().checkCapture()) {
        mIsCapture = true;
    }
}

}}}}  // namespace scn::step::boss::watergalboros
