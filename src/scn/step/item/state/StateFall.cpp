#include "scn/step/item/state/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/MapColl.h"
#include "scn/step/item/Param.h"
#include "scn/step/item/RotAnim.h"

namespace scn {
namespace step {
namespace item {
namespace state {

StateFall::StateFall(Item* item)
    : StateBase(item)
    , mCliffEdgeBoundCtrl(*item, item->param()._14, item->param()._18) {
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_SLOW);
    obj().mapColl().setValid(true);
    obj().landConstraint().setMode(static_cast<chara::LandConstraint::Mode>(2));
}

StateFall::~StateFall() {
    obj().mapColl().setValid(false);
}

void StateFall::procAnim() {
    mCliffEdgeBoundCtrl.update();
}

void StateFall::procMove() {
    const Param& param = obj().param();
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(param._4), gobj::MoveParamFall::Create(param._C, param._8, param._10));
}

void StateFall::procFixPos() {
    bool isGround = false;
    if (obj().mapColl().isHit()) {
        if (0.5f < obj().mapColl().normal().y) {
            obj().move().resetVelocity();
            if (!mCliffEdgeBoundCtrl.chkBound()) {
                isGround = true;
            }
        } else if (0.5f < hel::math::Math::AbsF32(obj().mapColl().normal().x)) {
            obj().move().setSpeedH(0.0f);
        }
    }
    if (isGround) {
        obj().footState().setGround();
    } else {
        obj().footState().setAir();
    }
}

}}}}  // namespace scn::step::item::state
