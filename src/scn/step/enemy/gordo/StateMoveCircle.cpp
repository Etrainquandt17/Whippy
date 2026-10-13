#include "scn/step/enemy/gordo/StateMoveCircle.h"

#include "gobj/FootState.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/gordo/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace gordo {

// TODO: the cast stands in for whatever made the original load the x coordinate ahead of the temporary's address.
StateMoveCircle::StateMoveCircle(Enemy* enemy)
    : StateBase(enemy)
    , mCenter(hel::math::Vector3(static_cast<f32>(enemy->location().pos().x), enemy->location().pos().y - obj().param().gordo().mCircleRadius, 0.0f))
    , mAngle(0.0f)
    , mRadius(0.0f)
    , mSpeed(0.0f) {
    const ParamData& param = obj().param().gordo();
    obj().footState().setAir();
    obj().model().reqScript(0);
    mAngle = Utility::GetRotByDirType(*enemy);
    switch (obj().variation()) {
    default:
        mRadius = param.mCircleRadius;
        break;
    case 0xd3:
    case 0xd4:
        mRadius = param.mCircleRadiusMiddle;
        break;
    case 0xd5:
    case 0xd6:
        mRadius = param.mCircleRadiusLarge;
        break;
    }
    switch (static_cast<u32>(obj().level())) {
    case 0:
        mSpeed = param.mCircleSpeedLv0;
        break;
    case 1:
        mSpeed = param.mCircleSpeedLv1;
        break;
    default:
        mSpeed = param.mCircleSpeedLv2;
        break;
    }
    f32 x = enemy->location().pos().x;
    mCenter.x = x - mRadius * hel::math::Math::SinDegF(mAngle);
    f32 y = enemy->location().pos().y;
    mCenter.y = y - mRadius * hel::math::Math::CosDegF(mAngle);
}

void StateMoveCircle::procMove() {
    mAngle += mSpeed;
    while (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    hel::math::Vector3 dir(hel::math::Math::SinDegF(mAngle), hel::math::Math::CosDegF(mAngle), 0.0f);
    if (obj().variation() == 0xd || obj().variation() == 0xd3 || obj().variation() == 0xd5) {
        dir.x = -dir.x;
    }
    dir *= mRadius;
    obj().location().setPos(dir + mCenter);
}

}
}
}
}
