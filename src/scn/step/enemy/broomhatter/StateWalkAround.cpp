#include "scn/step/enemy/broomhatter/StateWalkAround.h"

#include "g3d/NodeAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/broomhatter/ParamData.h"
#include "scn/step/enemy/common/StateFall.h"
#include "snd/SERequestor.h"

using g3d::NodeAccessor;
using hel::math::Direction3;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

StateWalkAround::StateWalkAround(Enemy* enemy) : StateBase(enemy), mTurnCount(0), mFrame(0), mSpeed(0.0f), mDecel(0.0f) {
    const ParamData& param = obj().param().broomhatter();
    obj().footState().setGround();
    initBrush();
    mSpeed = 2.0f * param.mWalkDistance / (param.mWalkEndFrame - param.mWalkStartFrame);
    mDecel = mSpeed / (param.mWalkEndFrame - param.mWalkStartFrame);
}

void StateWalkAround::procAnim() {
    const ParamData& param = obj().param().broomhatter();
    if (obj().model().isAllEnd()) {
        if (++mTurnCount >= obj().param().broomhatter().mWalkAroundTurnCount) {
            obj().target().setIsRightDir(!obj().target().isRightDir());
            mTurnCount = 0;
        }
        initBrush();
    }
    mFrame++;
    if (mFrame == param.mWalkStartFrame) {
        obj().move().setSpeedH(mSpeed * obj().target().getSign());
    }
    if (mFrame == param.mWalkEffectFrame) {
        NodeAccessor node = obj().model().model().nodes().at(1);
        Vector3 pos = node.worldMtx().getT();
        pos.y -= param.mWalkEffectOffsetY;
        Direction3 dir;
        if (!obj().target().isRightDir()) {
            dir.mLeft = -dir.mLeft;
        }
        obj().effect().normal().requestPD(static_cast<effect::Kind>(0x4b), pos, dir);
        obj().soundSE().start(0x302);
    }
}

void StateWalkAround::procMove() {
    obj().move().groundDecel(gobj::MoveParamDecel::Create(mDecel));
}

void StateWalkAround::procFixPos() {
    if (obj().mapColl().result()._2 || obj().cliffChecker().isCliff()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
        mTurnCount = 0;
        initBrush();
    }
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateFall, Enemy*>(objPtr());
    } else {
        obj().move().resetSpeedV();
    }
}

void StateWalkAround::initBrush() {
    obj().model().reqScript(3);
    obj().move().resetSpeedH();
    mFrame = 0;
}

}}}}  // namespace scn::step::enemy::broomhatter
