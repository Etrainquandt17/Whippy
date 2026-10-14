#include "scn/step/item/state/StateWithLowper.h"

#include "gobj/Location.h"
#include "gobj/Move.h"
#include "hel/math/Math.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Model.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/Param.h"
#include "scn/step/item/RotAnim.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace item {
namespace state {

StateWithLowper::StateWithLowper(Item* item)
    : StateBase(item)
    , mBasePos(item->initPos().toVector3())
    , mAngle(0.0f) {
    mAngle = static_cast<int>(obj().variation()) != 5 ? 0.0f : 180.0f;
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_SLOW);
    obj().model().reqScript(1);
    obj().setCanCatch(false);
    obj().culling().setValid(false);
    mBasePos.y += -1.0f;
}

StateWithLowper::~StateWithLowper() {
    obj().setCanCatch(false);
}

void StateWithLowper::procAnim() {
    mAngle += obj().param()._E4;
    while (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    f32 radius = obj().param()._EC;
    Vector3 offs(
        Math::SinDegF(mAngle) / radius, Math::CosDegF(mAngle) / radius, 0.0f);
    obj().move().setVelocity(Vector3(mAngle, mAngle, mAngle));
    obj().location().setPos(mBasePos + offs);
}

}}}}  // namespace scn::step::item::state
