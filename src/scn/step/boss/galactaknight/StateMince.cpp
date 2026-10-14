#include "scn/step/boss/galactaknight/StateMince.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateMince::StateMince(Boss* boss) : StateBase(boss) {
    const Param& param = obj().param().galactaknight();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0x11);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    custom.captureCtrl().setCaptureKind(CaptureCtrl::CAPTURE_KIND_1);
    Vector3 pos = obj().location().centerPos();
    pos.x += param._C4 * obj().target().getSign();
    custom.captureCtrl().setConstraintPos(pos);
}

StateMince::~StateMince() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().clearCapture();
}

void StateMince::procAnim() {
    if (obj().model().isAllEnd()) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().reqStateFinish();
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateMince::procMove() {}

void StateMince::procFixPos() {}

void StateMince::procObjCollReact() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().checkCapture();
}

}}}}  // namespace scn::step::boss::galactaknight
