#include "scn/step/enemy/tsukikage/StateJumpAttack.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/tsukikage/Custom.h"
#include "scn/step/enemy/tsukikage/ParamData.h"
#include "scn/step/enemy/tsukikage/StateFall.h"
#include "scn/step/enemy/tsukikage/StateLanding.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateJumpAttack::StateJumpAttack(Enemy* enemy)
    : StateBase(enemy), mFrame(0), mAttackFrame(0), mIsAttack(false), mIsFall(false), mIsAttackEnd(false) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    Utility::TurnHero(obj());
}

void StateJumpAttack::procAnim() {
    const ParamData& param = obj().param().tsukikage();
    u32 index = obj().model().anim().currentG3DAnimIndex();
    if (mFrame < param.mJumpAttackStartFrame) {
        mFrame++;
    }
    if (mFrame == param.mJumpStartFrame) {
        obj().soundSE().start(0x2dc);
        obj().model().reqScript(8);
    }
    if (mFrame == param.mJumpAttackStartFrame && index == 6) {
        obj().model().reqScript(9);
        if (obj().target().isRightDir()) {
            obj().effect().state().requestN(static_cast<effect::Kind>(0x4a3), 0);
        } else {
            obj().effect().state().requestN(static_cast<effect::Kind>(0x4a2), 0);
        }
        mIsAttack = true;
    }
    if (index == 7) {
        if (mAttackFrame < param.mShurikenFrame + param.mJumpAttackEndFrame) {
            mAttackFrame++;
        }
        if (mAttackFrame == param.mShurikenFrame) {
            obj().soundSE().start(0x2ee);
            DynamicCastToRef<Custom, ICustom>(obj().custom()).requestShuriken();
        } else if (mAttackFrame == param.mShurikenFrame + param.mJumpAttackEndFrame) {
            mIsAttackEnd = true;
        }
        if (obj().model().isAllEnd()) {
            obj().model().reqScript(1);
        } else if (obj().move().velocity().y < 0.0f && !mIsFall) {
            mIsFall = true;
        }
    }
}

void StateJumpAttack::procMove() {
    const ParamData& param = obj().param().tsukikage();
    if (mFrame >= param.mJumpStartFrame) {
        if (obj().footState().isGround()) {
            obj().footState().setAir();
            obj().move().setVelocity(Vector3(0.0f, param.mJumpSpeedYHigh, 0.0f));
        }
        if (!mIsFall || mIsAttackEnd) {
            obj().move().airDecelFall(param.mFallDecel, param.mFall);
        } else if (mIsFall && !mIsAttackEnd) {
            obj().move().resetSpeedV();
        }
    }
}

void StateJumpAttack::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && mFrame > obj().param().tsukikage().mJumpStartFrame) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<StateLanding, Enemy*>(objPtr());
    } else if (!obj().mapColl().result().mIsHitFloor && obj().footState().isGround()) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::tsukikage
