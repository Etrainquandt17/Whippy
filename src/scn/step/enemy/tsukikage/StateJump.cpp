#include "scn/step/enemy/tsukikage/StateJump.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/tsukikage/Custom.h"
#include "scn/step/enemy/tsukikage/ParamData.h"
#include "scn/step/enemy/tsukikage/StateFall.h"
#include "scn/step/enemy/tsukikage/StateLanding.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateJump::StateJump(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    Utility::TurnHero(obj());
}

StateJump::~StateJump() {}

void StateJump::procAnim() {
    if (++mFrame == obj().param().tsukikage().mJumpStartFrame) {
        obj().soundSE().start(0x2dc);
        obj().model().reqScript(8);
    }
    if (obj().move().velocity().y <= 0.0f && static_cast<u32>(obj().model().anim().currentG3DAnimIndex()) == 6) {
        obj().model().reqScript(1);
    }
}

void StateJump::procMove() {
    const ParamData& param = obj().param().tsukikage();
    if (mFrame >= param.mJumpStartFrame) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            setJumpSpeed();
        }
        obj().move().airDecelFall(param.mFallDecel, param.mFall);
    }
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && mFrame > obj().param().tsukikage().mJumpStartFrame) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    } else if (!obj().mapColl().result().mIsHitFloor && obj().footState().isGround()) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    } else if (obj().mapColl().result()._2) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
}

void StateJump::setJumpSpeed() {
    f32 dir = 1.0f;
    f32 x = obj().location().pos().x;
    if (Utility::GetNearestPlayerPos(obj()).x - x >= 0.0f) {
        dir = -1.0f;
    }
    const ParamData& param = obj().param().tsukikage();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 speedX;
    f32 speedY;
    switch (custom.getJumpNum()) {
    default:
        speedY = param.mJumpSpeedY;
        speedX = 0.0f;
        break;
    case 1:
        speedY = param.mJumpSpeedYHigh;
        speedX = 0.0f;
        break;
    case 2:
        speedY = param.mJumpSpeedY;
        speedX = -1.0f * param.mJumpSpeedX * dir;
        break;
    case 3:
        speedY = param.mJumpSpeedY;
        speedX = param.mJumpSpeedX * dir;
        break;
    }
    obj().move().setVelocity(hel::math::Vector3(speedX, speedY, 0.0f));
}

}}}}  // namespace scn::step::enemy::tsukikage
