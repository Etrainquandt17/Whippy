#include "scn/step/enemy/walf/StateMoveInWater.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Water.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/walf/Custom.h"
#include "scn/step/enemy/walf/ParamData.h"
#include "scn/step/enemy/walf/StateMoveOnWater.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

StateMoveInWater::StateMoveInWater(Enemy* enemy)
    : StateBase(enemy)
    , mJumpCounter(enemy->param().walf().mInWaterJumpFrame + 1)
    , mMoveCounter(enemy->param().walf().mInWaterFrame)
    , mIsFloating(false) {
    obj().footState().setAir();
    obj().model().reqScript(8);
}

void StateMoveInWater::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mMoveCounter.advanceIfNotEnd();
    if (mMoveCounter.isEnd()) {
        if (mIsFloating) {
            if (obj().variation() == 0xe1 && custom.checkTurnAfterJump()) {
                obj().target().setIsRightDir(!obj().target().isRightDir());
            }
            obj().stateChanger().setNextState<StateMoveOnWater, Enemy*>(objPtr());
        } else {
            mMoveCounter.reset();
            obj().model().reqScript(8);
            setBubbleEffect();
        }
    }
}

void StateMoveInWater::procMove() {
    const ParamData& param = obj().param().walf();
    mJumpCounter.advanceIfNotEnd();
    if (mJumpCounter.frame() == param.mInWaterJumpFrame) {
        obj().move().setVelocity(hel::math::Vector3(param.mInWaterSpeedH * obj().target().getSign(), param.mInWaterSpeedV, 0.0f));
    }
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMoveInWater::procFixPos() {
    const ParamData& param = obj().param().walf();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    hel::math::Vector2 offset = param.mInWaterWallOffset;
    offset.x *= obj().target().getSign();
    offset.y -= 0.3f;
    if (obj().mapColl().result()._2 || !obj().water().isPosInWater(offset) || Utility::ChkNururiByDir(obj(), 0.1f)) {
        f32 x = obj().move().velocity().x * -1.0f;
        f32 y = obj().move().velocity().y;
        obj().move().setVelocity(hel::math::Vector3(x, y, 0.0f));
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
    if (custom.isFloating()) {
        obj().move().setSpeedV(0.0f);
        mIsFloating = true;
    }
}

void StateMoveInWater::setBubbleEffect() {
    if (!mIsFloating && obj().water().isPosInWater(hel::math::Vector2(0.0f, 1.0f))) {
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x133), obj().location().centerPos());
    }
}

}
}
}
}
