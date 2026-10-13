#include "scn/step/enemy/goliathiceball/StateFall.h"

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
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/goliathiceball/StateWallHit.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace goliathiceball {

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
    g3d::NodeAccessor node = obj().model().model().nodes().at(1);
    hel::math::Vector3 rot(mRot, 0.0f, 0.0f);
    node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(rot));
}

void StateFall::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().stateChanger().setNextState<StateWallHit, Enemy*>(objPtr());
    }
}

}
}
}
}
