#include "scn/step/enemy/brontoburt/StatePursuit.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/brontoburt/ParamData.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace brontoburt {

StatePursuit::StatePursuit(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().move().setVelocity(Vector3(0.0f, 0.0f, 0.0f));
}

void StatePursuit::procMove() {
    if (Utility::IsPlayerExist(obj())) {
        f32 maxSpeed;
        f32 accel;
        switch (obj().level()) {
    case 0:
        maxSpeed = obj().param().brontoburt().mFlySpeed[0];
        accel = obj().param().brontoburt().mFlyAccel[0];
        break;
    case 1:
        maxSpeed = obj().param().brontoburt().mFlySpeed[1];
        accel = obj().param().brontoburt().mFlyAccel[1];
        break;
    case 2:
        maxSpeed = obj().param().brontoburt().mFlySpeed[2];
        accel = obj().param().brontoburt().mFlyAccel[2];
        break;
    default:
        maxSpeed = obj().param().brontoburt().mFlySpeed[3];
        accel = obj().param().brontoburt().mFlyAccel[3];
        break;
        }
        Vector3 velocity = obj().move().velocity();
        Vector3 dir = Utility::GetNearestPlayerPos(obj()).toVector3() - obj().location().pos();
        if (!dir.isZeroLoose(0.00001f)) {
            dir.normalize();
            velocity += dir * accel;
            f32 speed = Math::SqrtF(velocity.squareLength());
            if (speed > maxSpeed) {
                velocity = velocity * maxSpeed / speed;
            }
            obj().move().setVelocity(velocity);
            obj().target().setIsRightDir(dir.x > 0.0f);
        }
    }
    obj().location().setPos(obj().location().pos() + obj().move().velocity());
}

// TODO: a stand-in. The original calls hel::math::Vector3::dot here, as a unit does that uses it twice, and no second
// use is known.
#pragma dont_inline on
void StatePursuit::procFixPos() {
    f32 bound = 2.0f;
    Vector3 velocity = obj().move().velocity();
    Vector3 nururiDir = obj().nururi().getNururiDir().toVector3();
    f32 dot = velocity.dot(nururiDir);
    if (dot < 0.0f) {
        velocity -= nururiDir * ((1.0f + bound) * dot / nururiDir.squareLength());
    }
    if (obj().mapColl().result()._2) {
        if ((velocity.x < 0.0f && !obj().target().isRightDir()) || (velocity.x > 0.0f && obj().target().isRightDir())) {
            velocity.x = -velocity.x * bound;
        }
    }
    if ((obj().mapColl().result().mIsHitRoof && velocity.y > 0.0f)
        || (obj().mapColl().result().mIsHitFloor && velocity.y < 0.0f)) {
        velocity.y = -velocity.y * bound;
    }
    obj().move().setVelocity(velocity);
    obj().target().setIsRightDir(velocity.x > 0.0f);
}

#pragma dont_inline reset

}}}}  // namespace scn::step::enemy::brontoburt
