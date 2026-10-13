#include "scn/step/enemy/rocky/StateWalk.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/CliffChecker.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/rocky/ParamData.h"
#include "scn/step/enemy/rocky/StateAttack.h"
#include "scn/step/enemy/rocky/StateCliffAttack.h"
#include "scn/step/enemy/rocky/StateFall.h"
#include "scn/step/enemy/rocky/StateSlope.h"
#include "scn/step/enemy/rocky/StateWalkEnd.h"
#include "scn/step/hero/Manager.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

StateWalk::StateWalk(Enemy* enemy) : StateBase(enemy), mIsMove(false), mFrame(0), mAttackFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(3);
    obj().move().resetSpeedV();
    obj().move().resetSpeedH();
    mFrame = app::Random::Rand(obj().param().rocky().mWalkRandFrame) + obj().param().rocky().mWalkBaseFrame;
    mAttackFrame = mFrame - obj().param().rocky().mWalkAttackWait;
}

StateWalk::~StateWalk() {}

void StateWalk::procAnim() {
    const ParamData& param = obj().param().rocky();
    mFrame--;
    f32 frame = obj().model().anim().frame();
    if ((param.mWalkMoveFrame[0] < frame && frame < param.mWalkMoveFrame[1]) ||
        (param.mWalkMoveFrame[2] < frame && frame < param.mWalkMoveFrame[3])) {
        obj().model().anim().setFrameRate(1.0f);
        mIsMove = true;
    } else {
        obj().model().anim().setFrameRate(param.mWalkFrameRate);
        mIsMove = false;
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(3);
    }
    if (mFrame <= 0) {
        obj().stateChanger().setNextState<StateWalkEnd, Enemy*>(objPtr());
    } else if (mFrame < mAttackFrame) {
        bool isFound = false;
        bool isRight = obj().target().isRightDir();
        u32 count = obj().comp().heroManager().getPlayerCount();
        for (u32 i = 0; i < count; i++) {
            hel::math::Vector3 diff = obj().comp().heroManager().getPlayerPosByIndex(i) - obj().location().pos();
            if (hel::math::Math::Abs(diff.x) < param.mStayAttackRangeX && diff.y < param.mStayAttackRangeTop &&
                diff.y > param.mStayAttackRangeBottom) {
                isFound = true;
                isRight = diff.x >= 0.0f;
                break;
            }
        }
        if (isFound) {
            obj().target().setIsRightDir(isRight);
            obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
        }
    }
}

void StateWalk::procMove() {
    if (mIsMove) {
        obj().move().setSpeedH(obj().param().rocky().mWalkSpeed * obj().target().getSign());
    }
    obj().move().groundDecel(obj().param().rocky().mWalkDecel);
}

void StateWalk::procFixPos() {
    Utility::ChkNururiTurn(obj());
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    } else if (obj().cliffChecker().isCliff()) {
        obj().stateChanger().setNextState<StateCliffAttack, Enemy*>(objPtr());
    } else if (obj().variation() == 0x2f) {
        hel::math::Vector2 normal = obj().mapColl().floorNormal();
        if (hel::math::Math::Abs(normal.x) >= obj().param().rocky().mWalkSlopeNormalX) {
            if ((normal.x < 0.0f && obj().target().isRightDir()) || (normal.x > 0.0f && !obj().target().isRightDir())) {
                obj().target().setIsRightDir(!obj().target().isRightDir());
            } else {
                obj().stateChanger().setNextState<StateSlope, Enemy*>(objPtr());
            }
        }
    }
    if (mIsMove && obj().mapColl().result()._2) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
}

}}}}  // namespace scn::step::enemy::rocky
