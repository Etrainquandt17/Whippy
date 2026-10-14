#include "scn/step/carryitem/abilitystar/StateDead.h"

#include "gobj/Location.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/core/PermEffect.h"

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

StateDead::StateDead(CarryItem* carryItem, bool isLong)
    : StateBase(carryItem)
    , mFrame(0)
    , mIsLong(isLong) {
    obj().setIsEnableCarry(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().worldCage().setIsValid(true);
    obj().move().resetVelocity();
    hel::math::Vector3 pos = obj().location().pos();
    if (obj().mapColl().result()._7) {
        obj().comp().permEffect().normal().requestForeP(static_cast<effect::Kind>(0xD9), pos);
    } else {
        obj().comp().permEffect().normal().requestForeP(static_cast<effect::Kind>(0xD8), pos);
    }
}

StateDead::~StateDead() {
    obj().worldCage().setIsValid(false);
    obj().move().resetMoveRate();
    obj().model().resetViewOffset();
}

void StateDead::procAnim() {
    mFrame++;
    if (mFrame < 15) {
        hel::math::Vector3 offset;
        f32 angle = 30.0f + 120.0f * static_cast<f32>((mFrame % 6) / 2);
        offset.x = 0.05f * hel::math::Math::CosDegF(angle);
        offset.y = 0.05f * hel::math::Math::SinDegF(angle);
        obj().model().setViewOffset(offset);
    }
    if (mIsLong) {
        if (mFrame >= 30) {
            obj().deadWithEffect();
        }
    } else if (mFrame >= 15) {
        obj().deadWithEffect();
    }
}

void StateDead::procMove() {
    if (mIsLong && mFrame > 20) {
        obj().move().airDecelFall(
            gobj::MoveParamDecel::Create(obj().param().abilityStar()._0),
            gobj::MoveParamFall::Create(
                obj().param().abilityStar()._8, obj().param().abilityStar()._4, obj().param().abilityStar()._C));
    } else {
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Create(0.0f, 0.0f, 0.0f));
    }
}

}}}}  // namespace scn::step::carryitem::abilitystar
