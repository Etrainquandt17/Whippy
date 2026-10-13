#include "scn/step/enemy/twister/StateRise.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
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
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/twister/Custom.h"
#include "scn/step/enemy/twister/ParamData.h"
#include "scn/step/enemy/twister/StateWait.h"
#include "scn/step/ocoll/AttackType.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

#ifdef VERSION_SUKK01
const effect::Kind t_riseEffectKind = static_cast<effect::Kind>(0x655);
#else
const effect::Kind t_riseEffectKind = static_cast<effect::Kind>(0x654);
#endif

StateRise::StateRise(Enemy* enemy)
    : StateBase(enemy), mIsRising(true), mFrame(0), mSpeedV(0.0f), mIsJump(false), mThetaSpeed(0.0f) {
    const ParamData& param = obj().param().twister();
    obj().model().anim().setFrameRate(0.0f);
    obj().effect().state().requestN(t_riseEffectKind, 0);
    obj().footState().setGround();
    obj().move().resetSpeedV();
    mThetaSpeed = param.mThetaYSpeed;
}

StateRise::~StateRise() {}

void StateRise::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().twister();
    mFrame++;
    custom.setThetaY(mThetaSpeed + custom.getThetaY());
    if (custom.getThetaX() > 0.0f) {
        custom.setThetaX(custom.getThetaX() - param.mThetaXMax / 10.0f);
    }
    obj().model().model().nodes().at(1).localMtx().setRTMtx(
        hel::math::Matrix34::CreateRotXYZDeg(hel::math::Vector3(custom.getThetaX(), custom.getThetaY(), 0.0f)));
    if (mIsRising == true) {
        if (mFrame <= param.mRiseFrame) {
            if (mFrame == param.mRiseStartFrame) {
                obj().soundSEState().start(0x2cd);
                obj().footState().setAir();
                mSpeedV = param.mRiseAccel;
                obj().move().setSpeedV(mSpeedV);
                mIsJump = true;
                obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x1a4));
            }
            mThetaSpeed = static_cast<f32>(mFrame) / 2.0f + param.mThetaYSpeed;
        }
        if (obj().move().velocity().y <= 0.0f && mFrame > 30) {
            mIsRising = false;
            mFrame = 0;
            obj().soundSEState().stop();
            obj().effect().state().release();
            obj().objColl().bodyColl().unsetAttackTypeOver();
        }
    } else if (mFrame <= param.mRiseFrame) {
        mThetaSpeed = static_cast<f32>(param.mRiseFrame - mFrame) / 2.0f + param.mThetaYSpeed;
    }
}

void StateRise::procMove() {
    const ParamData& param = obj().param().twister();
    if (obj().footState().isAir()) {
        if (mIsJump == true) {
            mSpeedV += param.mRiseAccel;
            obj().move().setSpeedV(mSpeedV);
            obj().move().airAccelFall(obj().target().isRightDir(), gobj::MoveParamAccel::Zero(), gobj::MoveParamFall::Zero());
            if (obj().move().velocity().y > 0.1f) {
                mIsJump = false;
            }
        } else if (mFrame > 10) {
            obj().move().airAccelFall(obj().target().isRightDir(), param.mRiseAccelH, param.mRiseFall);
        }
    }
}

void StateRise::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor && obj().footState().isAir() && mFrame > obj().param().twister().mRiseStartFrame) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(objPtr());
        obj().move().resetSpeedV();
    }
}

}
}
}
}
