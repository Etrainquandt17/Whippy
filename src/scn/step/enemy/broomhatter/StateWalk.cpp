#include "scn/step/enemy/broomhatter/StateWalk.h"

#include "g3d/NodeAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/broomhatter/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

StateWalk::StateWalk(Enemy* enemy) : StateBase(enemy), mFrame(0), mSpeed(0.0f), mDecel(0.0f) {
    const ParamData& param = obj().param().broomhatter();
    obj().footState().setGround();
    mSpeed = 2.0f * param.mWalkDistance / (param.mWalkEndFrame - param.mWalkStartFrame);
    mDecel = mSpeed / (param.mWalkEndFrame - param.mWalkStartFrame);
    obj().model().reqScript(3);
}

void StateWalk::procAnim() {
    const ParamData& param = obj().param().broomhatter();
    mFrame++;
    if (mFrame == param.mWalkStartFrame) {
        obj().move().setSpeedH(mSpeed * obj().target().getSign());
    }
    if (mFrame == param.mWalkEffectFrame) {
        g3d::NodeAccessor node = obj().model().model().nodes().at(1);
        hel::math::Vector3 pos = node.worldMtx().getT();
        pos.y -= param.mWalkEffectOffsetY;
        hel::math::Direction3 dir;
        dir.mLeft *= obj().target().getSign();
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x4b), pos, dir);
        obj().soundSE().start(0x302);
    }
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateWalk::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(mDecel));
}

void StateWalk::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    }
}

}
}
}
}
