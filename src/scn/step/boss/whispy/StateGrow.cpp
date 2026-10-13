#include "scn/step/boss/whispy/StateGrow.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/boss/whispy/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Model.h"
#include "scn/step/info/BossPanel.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateGrow::StateGrow(Boss* boss) : StateBase(boss), mCount(0) {
    obj().invincible().setPermNoFlash();
    obj().model().reqScript(0xE);
    obj().infoBossPanel().transformStart();
}

StateGrow::~StateGrow() {
    obj().infoBossPanel().transformEnd();
}

void StateGrow::procAnim() {
    const Param& param = obj().param().whispy();
    mCount++;
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    f32 rate = static_cast<f32>(mCount) / static_cast<f32>(param.mGrowFrame);
    if (rate > 1.0f) {
        rate = 1.0f;
    }
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.tsctrl().setTrunkScale(hel::math::Math::LinearInterpolation(1.0f, param.mGrowTrunkScale, rate));
    hel::math::Vector3 trans = hel::math::Vector3(param.mGrowBaseTrans) * rate;
    custom.tsctrl().setBaseTrans(trans);
    hel::math::Vector3 scale =
        hel::math::Math::LinearInterpolation(hel::math::Vector3::ALL_ONE, hel::math::Vector3(param.mGrowBaseScale), rate);
    custom.tsctrl().setBaseScale(scale);
    hel::geo::Rect rect(param.mLockRect[0], param.mLockRect[1], param.mLockRect[2], param.mLockRect[3]);
    rect.trans(param.mGrowLockTransX * rate, param.mGrowLockTransY * rate);
    obj().comp().cameraController().setLock(rect);
}

void StateGrow::procMove() {}

void StateGrow::procFixPos() {}

}
}
}
}
