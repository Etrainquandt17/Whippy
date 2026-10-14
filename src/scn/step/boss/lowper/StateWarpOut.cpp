#include "scn/step/boss/lowper/StateWarpOut.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateWarpOut::StateWarpOut(Boss* boss, const Vector3& pos) : StateBase(boss), mCount(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().model().reqScript(0x19);
    Rect rect = obj().comp().mainCamera().getViewRect();
    f32 width = Math::AbsF32(rect._C - rect._8);
    Vector3 offset = pos;
    offset.x = Math::Limit(offset.x, 0.5f * width - 1.5f);
    custom.waftMoveCtrl().setCenter(obj().basePos().toVector3() + offset);
    custom.waftMoveCtrl().setMoveIntpRate(0.1f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    obj().model().setScale(Vector3(0.01f, 2.0f, 0.01f));
    obj().location().setPos(obj().basePos().toVector3() + offset);
    f32 baseX = obj().basePos().x;
    obj().target().setIsRightDir(obj().location().pos().x < baseX);
}

StateWarpOut::~StateWarpOut() {
    obj().model().setVisibility(true);
    obj().model().resetScale();
}

void StateWarpOut::procAnim() {
    mCount++;
    if (mCount < 40) {
        mCount++;
        if (mCount == 40) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
    }
    f32 t = static_cast<f32>(mCount) / 40.0f;
    Vector3 scale(t, (1.0f - t) * (1.0f - t) + 1.0f, t);
    obj().model().setScale(scale);
}

void StateWarpOut::procMove() {}

void StateWarpOut::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
