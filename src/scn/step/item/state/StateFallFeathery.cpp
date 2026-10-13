#include "scn/step/item/state/StateFallFeathery.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/MapColl.h"
#include "scn/step/item/Param.h"
#include "scn/step/item/RotAnim.h"

namespace scn {
namespace step {
namespace item {
namespace state {

StateFallFeathery::StateFallFeathery(Item* item)
    : StateBase(item)
    , mFallSpeed(obj().param()._24) {
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_SLOW);
    obj().mapColl().setValid(true);
}

StateFallFeathery::~StateFallFeathery() {
    obj().mapColl().setValid(false);
}

void StateFallFeathery::procAnim() {}

void StateFallFeathery::procMove() {
    const Param& param = obj().param();
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(param._1C), gobj::MoveParamFall::Create(mFallSpeed, param._20, param._30));
    mFallSpeed -= param._28;
    if (mFallSpeed < param._2C) {
        mFallSpeed = param._2C;
    }
}

void StateFallFeathery::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().move().resetVelocity();
    }
}

}}}}  // namespace scn::step::item::state
