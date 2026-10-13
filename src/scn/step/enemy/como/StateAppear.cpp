#include "scn/step/enemy/como/StateAppear.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/como/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

StateAppear::StateAppear(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().model().reqScript(0);
    obj().soundSE().start(0x2AD);
}

void StateAppear::procAnim() {
    const ParamData& param = obj().param().como();
    mFrame++;
    if (mFrame == param.mAppearFrame + param.mAppearWaitFrame) {
        obj().soundSE().start(0x2BD);
        obj().stateChanger().setNextState<common::StateFly, Enemy*>(objPtr());
    }
}

void StateAppear::procMove() {
    const ParamData& param = obj().param().como();
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param.mAppearFrame);
    if (rate > 1.0f) {
        rate = 1.0f;
    }
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 length = param.mAppearLength * hel::math::Math::SinDegF(90.0f * rate);
    custom.threadCtrl().setLength(length);
}

void StateAppear::procFixPos() {}

}
}
}
}
