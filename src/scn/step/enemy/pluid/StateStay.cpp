#include "scn/step/enemy/pluid/StateStay.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/pluid/Custom.h"
#include "scn/step/enemy/pluid/ParamData.h"
#include "snd/SERequestor.h"

using app::Random;
using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

StateStay::StateStay(Enemy* enemy) : StateBase(enemy), mIsExistLand(true), _9(false), mFrame(0), mWaitFrame(0), mFallFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    int rand = Random::Rand(10);
    mWaitFrame = (rand + 1) * obj().param().pluid().mStayFrameUnit;
    obj().model().rotCtrl().setRotHTarget(0.0f);
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x565), 0, Direction3::BASIS);
}

StateStay::~StateStay() {}

void StateStay::procAnim() {
    if (mFallFrame == obj().param().pluid().mStayFallAnimFrame) {
        obj().model().reqScript(1);
    }
}

void StateStay::procMove() {
    bool isFall;
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isRandomFall()) {
        mFrame++;
        isFall = mFrame >= mWaitFrame;
    } else {
        isFall = isPlayerNear();
    }
    isExistLand();
    if (isFall || !mIsExistLand) {
        if (++mFallFrame == 1) {
            obj().effect().normal().release();
            Utility::TurnHero(obj());
            obj().soundSE().start(0x2d0);
        }
        DynamicCastToRef<Custom, ICustom>(obj().custom()).setRotate(0.0f);
        obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), obj().param().pluid().mStayFall);
    }
}

void StateStay::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().effect().normal().requestP(static_cast<effect::Kind>(0x563), obj().location().pos());
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

bool StateStay::isPlayerNear() {
    Vector2 pos = obj().location().pos().getXY();
    Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
    if (pos.y >= playerPos.y && pos.x - 2.5f <= playerPos.x && playerPos.x <= 2.5f + pos.x) {
        return true;
    }
    return false;
}

void StateStay::isExistLand() {
    int x = static_cast<int>(obj().location().pos().x);
    int y = static_cast<int>(obj().location().pos().y) + 1;
    if (!Utility::IsExistLand(obj(), static_cast<f32>(x), static_cast<f32>(y))) {
        mIsExistLand = false;
    }
}

}}}}  // namespace scn::step::enemy::pluid
