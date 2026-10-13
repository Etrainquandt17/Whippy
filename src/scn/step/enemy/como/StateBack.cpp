#include "scn/step/enemy/como/StateBack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/como/Custom.h"
#include "scn/step/enemy/como/ParamData.h"
#include "scn/step/enemy/como/StateCutFall.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

StateBack::StateBack(Enemy* enemy)
    : StateBase(enemy), mFrame(0),
      mStartLength(hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().getLength()) {
    obj().model().reqScript(0);
}

void StateBack::procAnim() {}

void StateBack::procMove() {
    const ParamData& param = obj().param().como();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    u32 frame = static_cast<u32>(mStartLength / param.mBackSpeed);
    if (frame == 0) {
        frame = 1;
    }
    mFrame++;
    if (mFrame <= frame) {
        f32 length = mStartLength * static_cast<f32>(frame - mFrame) / static_cast<f32>(frame);
        f32 angle = 180.0f * static_cast<f32>(mFrame) / static_cast<f32>(param.mBackSwingFrame);
        length -= param.mBackSwingLength * hel::math::Math::Abs(hel::math::Math::SinDegF(angle));
        custom.threadCtrl().setLength(length);
    } else {
        obj().stateChanger().setNextState<common::StateFly, Enemy*>(objPtr());
    }
}

void StateBack::procFixPos() {}

void StateBack::procObjCollReact() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).threadCtrl().checkCut()) {
        obj().stateChanger().setNextState<StateCutFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::como
