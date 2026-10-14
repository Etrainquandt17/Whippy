#include "scn/step/item/state/StateBound.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/item/Item.h"
#include "scn/step/item/MapColl.h"
#include "scn/step/item/Param.h"
#include "scn/step/item/RotAnim.h"
#include "scn/step/map/KindUtil.h"

using app::Random;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace item {
namespace state {

StateBound::StateBound(Item* item)
    : StateBase(item)
    , mCliffEdgeBoundCtrl(*item, item->param()._5C, item->param()._60) {
    const Param& param = obj().param();
    obj().rotAnim().setSpeed(RotAnim::SPEED_KIND_SLOW);
    obj().mapColl().setValid(true);
    obj().move().setSpeedV(param._34);
    f32 speedH = param._38;
    if (map::KindUtil::IsChallengeStage(obj().comp().context().mapKind)) {
        speedH = param._3C;
    }
    obj().move().setSpeedH(speedH * Random::RandAF());
}

StateBound::~StateBound() {
    obj().mapColl().setValid(false);
    obj().deleteObjGenerator();
}

void StateBound::procAnim() {
    mCliffEdgeBoundCtrl.update();
    obj().deleteObjGenerator();
}

void StateBound::procMove() {
    const Param& param = obj().param();
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(param._40), gobj::MoveParamFall::Create(param._48, param._44, param._4C));
}

void StateBound::procFixPos() {
    const Param& param = obj().param();
    if (obj().mapColl().isHit()) {
        Vector3 velocity = obj().move().velocity();
        if (0.0f < obj().mapColl().normal().y) {
            velocity.x *= param._50;
            velocity.y *= -param._54;
            if (velocity.y > param._58) {
                velocity.y = param._58;
            }
        }
        if (Math::Abs(obj().mapColl().normal().x) > 0.75f) {
            velocity.x *= -1.0f;
        }
        if (obj().mapColl().normal().y < -0.75f) {
            velocity.y = -1.0f * Math::Abs(velocity.y);
        }
        mCliffEdgeBoundCtrl.chkBound();
        obj().move().setVelocity(velocity);
        if (velocity.isZeroLoose(0.00001f)) {
            obj().footState().setGround();
        } else {
            obj().footState().setAir();
        }
    }
}

}}}}  // namespace scn::step::item::state
