#include "scn/step/enemy/gordo/StateMoveSinCurve.h"

#include "gobj/FootState.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/gordo/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

namespace {

// TODO: chara::MapCollResult::isHitWall(), which the shared header declares without its body.
inline bool t_IsHitWall(const chara::MapCollResult& result) {
    return result._2 || result._3;
}

}

StateMoveSinCurve::StateMoveSinCurve(Enemy* enemy)
    : StateBase(enemy), mBase(hel::math::Vector3(enemy->location().pos().x, enemy->location().pos().y, 0.0f)), mAngle(0.0f) {
    obj().footState().setAir();
    obj().model().reqScript(0);
}

void StateMoveSinCurve::procMove() {
    const ParamData& param = obj().param().gordo();
    mAngle += param.mCircleSpeedLv1;
    while (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    hel::math::Vector3 offset;
    if (obj().dirType() == 2 || obj().dirType() == 3) {
        offset.x = hel::math::Math::SinDegF(mAngle);
        offset.y = 0.0f;
    } else {
        offset.x = 0.0f;
        offset.y = hel::math::Math::SinDegF(mAngle);
    }
    offset *= param.mCircleRadius;
    obj().location().setPos(offset + mBase);
}

void StateMoveSinCurve::procFixPos() {
    const ParamData& param = obj().param().gordo();
    if (obj().mapColl().result().mIsHitRoof && obj().dirType() != 2 && obj().dirType() != 3) {
        mAngle = 90.0f;
        f32 offset = param.mCircleRadius * hel::math::Math::SinDegF(mAngle);
        mBase.y = obj().location().pos().y - offset;
    }
    if (obj().mapColl().result().mIsHitFloor && obj().dirType() != 2 && obj().dirType() != 3) {
        mAngle = 270.0f;
        f32 offset = param.mCircleRadius * hel::math::Math::SinDegF(mAngle);
        mBase.y = obj().location().pos().y - offset;
    }
    if (t_IsHitWall(obj().mapColl().result()) && (obj().dirType() == 2 || obj().dirType() == 3)) {
        if (mAngle > 90.0f && mAngle <= 270.0f) {
            mAngle = 270.0f;
        } else {
            mAngle = 90.0f;
        }
        f32 offset = param.mCircleRadius * hel::math::Math::SinDegF(mAngle);
        mBase.x = obj().location().pos().x - offset;
    }
}

}}}}  // namespace scn::step::enemy::gordo
