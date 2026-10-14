#include "scn/step/enemy/mopoo/StateHide.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/mopoo/Custom.h"
#include "scn/step/enemy/mopoo/ParamData.h"
#include "scn/step/enemy/mopoo/StateLaunch.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace mopoo {

StateHide::StateHide(Enemy* enemy) : StateBase(enemy), mFrame(0), mWaitTime(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
    obj().captureReceiver().setCanCapture(false);
    obj().vacuumReceiver().setResistLevel(2);
    obj().objColl().clearBodyColl();
    mWaitTime = obj().param().mopoo().mHideWaitTime;
    if (mWaitTime < custom.waitTime()) {
        mWaitTime = custom.waitTime();
    }
}

void StateHide::procFixPos() {
    const ParamData& param = obj().param().mopoo();
    bool isConst = DynamicCastToRef<Custom, ICustom>(obj().custom()).isVariationConst();
    bool isInRange = Utility::IsHeroInRange(obj(), param.mRangeLeft, param.mRangeRight, param.mRangeTop, param.mRangeBottom);
    if (mFrame <= mWaitTime) {
        mFrame++;
    }
    if (mFrame > mWaitTime) {
        if (isConst) {
            obj().stateChanger().setNextState<StateLaunch, Enemy*>(objPtr());
        } else if (isInRange) {
            obj().stateChanger().setNextState<StateLaunch, Enemy*>(objPtr());
        }
    }
}

}}}}  // namespace scn::step::enemy::mopoo
