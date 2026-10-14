#include "scn/step/item/state/StateRoah.h"

#include "app/Random.h"
#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Model.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/MapColl.h"
#include "scn/step/item/Param.h"
#include "scn/step/item/RotAnim.h"

using app::Random;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace item {
namespace state {

StateRoah::StateRoah(Item* item)
    : StateBase(item)
    , mFrame(0)
    , mStartY(0.0f)
    , mTargetY(0.0f) {
    const Param& param = obj().param();
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_MIDDLE);
    obj().model().reqScript(0);
    obj().mapColl().setValid(false);
    mStartY = item->initPos().y;
    mTargetY = item->comp().mainCamera().getCenter().y;
    if (obj().kind() == 0) {
        f32 range = 0.5f * param._114;
        switch (obj().subKind()) {
        case 0:
            mTargetY += range * Random::RandNF() + range;
            break;
        case 1:
        case 4:
            mTargetY += range * Random::RandNF();
            break;
        case 2:
            mTargetY -= range * Random::RandNF() + range;
            break;
        case 3:
        case 5:
            mTargetY -= range * Random::RandNF();
            break;
        }
    } else {
        mTargetY += param._114 * Random::RandAF();
    }
}

StateRoah::~StateRoah() {}

void StateRoah::procAnim() {
    mFrame++;
}

void StateRoah::procMove() {
    const Param& param = obj().param();
    if (mFrame <= param._118) {
        f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._118);
        f32 rate = Math::SinDegF(90.0f * t);
        f32 y = rate * (mTargetY - mStartY) + mStartY;
        obj().move().setSpeedV(y - obj().location().pos().y);
    }
    obj().move().accel(
        Vector3::BASIS_X * -1.0f, gobj::MoveParamAccel::Create(param._11C, param._120, param._124));
}

void StateRoah::procFixPos() {}

}}}}  // namespace scn::step::item::state
