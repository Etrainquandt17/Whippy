#include "scn/step/enemy/goliathsnowball/StateFall.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/goliathsnowball/StateWallHit.h"

using g3d::NodeAccessor;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace goliathsnowball {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy), mRot(0.0f) {
    obj().footState().setAir();
    obj().nururi().setCanNururi(false);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {
    mRot -= 10.0f;
    if (mRot < 0.0f) {
        mRot += 360.0f;
    }
    NodeAccessor node = obj().model().model().nodes().at(1);
    Vector3 rot(mRot, 0.0f, 0.0f);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(rot));
}

void StateFall::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.0005f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.3f, 0.01f, 0.01f);
    obj().move().airDecelFall(decel, fall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().stateChanger().setNextState<StateWallHit, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::goliathsnowball
