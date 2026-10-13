#include "scn/step/enemy/whispyapple/StateBoundNear.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/GroundChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/whispyapple/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

StateBoundNear::StateBoundNear(Enemy* enemy, bool flag) : StateBase(enemy), mRot(0.0f), mRotX(0.0f), mFloorY(0.0f), mSpeedV(0.0f) {
    obj().footState().setAir();
    mFloorY = obj().groundChecker().getFloorPos().y;
    mRot = obj().model().rotCtrl().getRotV();
    const ParamData& param = obj().param().whispyapple();
    hel::math::Vector3 velocity;
    if (flag) {
        velocity = param.mNearVelocityFar;
    } else {
        velocity = param.mNearVelocity;
    }
    velocity.x *= obj().target().getSign();
    obj().move().setVelocity(velocity);
    mSpeedV = velocity.y;
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
}

StateBoundNear::~StateBoundNear() {}

void StateBoundNear::procAnim() {
    const ParamData& param = obj().param().whispyapple();
    mRot += param.mNearRotSpeed * obj().target().getSign();
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    obj().model().rotCtrl().initRotV(mRot);
    mRotX += param.mNearRotXSpeed;
    if (mRotX >= 360.0f) {
        mRotX -= 360.0f;
    }
    if (mRotX < 0.0f) {
        mRotX += 360.0f;
    }
    Utility::SetCustomMtxRotate(obj(), hel::math::Vector3(mRotX, 0.0f, 0.0f));
}

void StateBoundNear::procMove() {
    const ParamData& param = obj().param().whispyapple();
    obj().move().airDecelFall(param.mDecel, param.mNearFall);
}

void StateBoundNear::procFixPos() {
    hel::math::Vector3 pos = obj().location().pos();
    const ParamData& param = obj().param().whispyapple();
    if (pos.z > param.mNearInvalidZ) {
        obj().vacuumReceiver().setIsValid(false);
    }
    if (pos.z < param.mNearBoundZ && pos.y < mFloorY) {
        pos.y = mFloorY;
        obj().location().setPos(pos);
        hel::math::Vector3 velocity = obj().move().velocity();
        velocity.y = hel::math::Math::LimitMax(-velocity.y, mSpeedV);
        obj().move().setSpeedV(velocity.y);
        f32 speedH = velocity.x * app::Random::RandF(param.mNearRandMin, param.mNearRandMax);
        obj().move().setSpeedH(speedH);
    }
}

}
}
}
}
