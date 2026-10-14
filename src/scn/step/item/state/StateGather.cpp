#include "scn/step/item/state/StateGather.h"

#include "gobj/Location.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/item/Catcher.h"
#include "scn/step/item/GetInfo.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/Param.h"
#include "scn/step/item/RotAnim.h"

using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace item {
namespace state {

StateGather::StateGather(Item* item, Catcher& catcher)
    : StateBase(item)
    , mFrame(0.0f)
    , mStartPos(obj().location().pos().getXY())
    , mCatcher(catcher) {
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_FAST);
    obj().setCanCatch(false);
    obj().setCanGather(false);
    Vector3 pos = obj().location().pos();
    pos.y += 0.5f;
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x77), pos);
}

void StateGather::procAnim() {
    mFrame += 1.0f;
    if (mFrame == static_cast<f32>(obj().param()._D8)) {
        mCatcher.addItem(GetInfo(obj().kind(), obj().subKind()));
        obj().onCatched();
        obj().dead();
    }
}

void StateGather::procMove() {
    f32 t = mFrame / 20.0f;
    f32 rate = 1.0f - (1.0f - t) * (1.0f - t);
    Vector2 catcherPos = mCatcher.getPos();
    Vector2 pos = catcherPos * rate;
    pos += mStartPos * (1.0f - rate);
    pos.y += Math::SinDegF(180.0f * t);
    obj().location().setPos(pos.toVector3());
}

}}}}  // namespace scn::step::item::state
