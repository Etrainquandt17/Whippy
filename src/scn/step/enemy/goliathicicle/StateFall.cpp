#include "scn/step/enemy/goliathicicle/StateFall.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/goliathicicle/StateFloorHit.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathicicle {

StateFall::StateFall(Enemy* enemy, f32 rot) : StateBase(enemy), mFall(0.0f), mFallAccel(0.0f), mRot(rot), mWaitFrame(0) {
    obj().footState().setAir();
    obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    obj().soundSE().start(0x37d);
    obj().nururi().setCanNururi(false);
    mWaitFrame = app::Random::RandU32(15);
}

StateFall::~StateFall() {}

void StateFall::procAnim() {
    if (mWaitFrame != 0) {
        mWaitFrame--;
    } else {
        mRot += 10.0f;
        if (mRot >= 360.0f) {
            mRot -= 360.0f;
        }
        g3d::NodeAccessor node = obj().model().model().nodes().at(0);
        hel::math::Vector3 rot(0.0f, mRot, 0.0f);
        node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(rot));
    }
}

void StateFall::procMove() {
    if (mWaitFrame == 0) {
        mFallAccel += 0.00001f;
        mFall += mFallAccel;
        gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.0005f);
        gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.75f, mFall, 0.01f);
        obj().move().airDecelFall(decel, fall);
    }
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().stateChanger().setNextState<StateFloorHit, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::goliathicicle
