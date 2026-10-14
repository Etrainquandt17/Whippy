#include "scn/step/weapon/mahoroaicicle/StateFall.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/mahoroaicicle/StateFloorHit.h"
#include "snd/SERequestor.h"
#include "util/StateChanger.h"

using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaicicle {

StateFall::StateFall(Weapon* weapon, f32 rot) : StateBase(weapon), mSpeed(0.0f), mAccel(0.0f), mRot(rot) {
    obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x40D), 0);
    obj().soundSE().start(0x429);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {
    mRot += 10.0f;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    obj().model().model().nodes().at(0).localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(0.0f, mRot, 0.0f)));
}

void StateFall::procMove() {
    mAccel += 0.00001f;
    mSpeed += mAccel;
    const gobj::MoveParamDecel& decel = gobj::MoveParamDecel::Create(0.0005f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.75f, mSpeed, 0.01f);
    obj().move().airDecelFall(decel, fall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().stateChanger().setNextState<StateFloorHit, Weapon*>(objPtr());
    }
}

}}}}  // namespace scn::step::weapon::mahoroaicicle
