#include "scn/step/boss/roah/StateZStar.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "snd/SERequestor.h"

using app::Random;
using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateZStar::StateZStar(Boss* boss, Config config) : StateBase(boss), mCount(0), mIndex(0), mBasePos(), mConfig(config) {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    mBasePos = obj().comp().mainCamera().getCenter().toVector3();
    mBasePos.x += mConfig._10 ? -param.mZStarOffset.x : param.mZStarOffset.x;
    mBasePos.y += param.mZStarOffset.y;
    mBasePos.z += param.mZStarOffset.z;
    obj().location().setPos(mBasePos);
    Vector3 target = mBasePos;
    if (mConfig._10) {
        target.x = param.mZStarOffset.x + obj().comp().mainCamera().getCenter().x;
    } else {
        target.x = obj().comp().mainCamera().getCenter().x - param.mZStarOffset.x;
    }
    custom.rotCtrl().toInvalid();
    // TODO: the original has sign in f24, below the constants the loop hoists (f25 to f31); here it takes f31.
    f32 sign = -1.0f;
    for (u32 i = 0; i < 6; i++) {
        f32 t = static_cast<f32>(i + 1) / 6.0f;
        t = param.mZStarCurve * Math::SinDegF(360.0f * t) + t;
        Vector3 pos = mBasePos * (1.0f - t) + target * t;
        pos.y += sign * (mConfig._4 * Random::RandNF() + mConfig._8);
        mPoints.add(pos);
        sign *= -1.0f;
    }
    Utility::ControlHateOnAction(obj());
}

StateZStar::~StateZStar() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).rotCtrl().toValid();
    mPoints.clear();
}

void StateZStar::procAnim() {
    const Param& param = obj().param().roah();
    if (mCount < mConfig._0) {
        mCount++;
    } else {
        mCount = 0;
        mIndex++;
        mBasePos = obj().location().pos();
        if (mIndex == 6) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
    }
    f32 rotY = param.mZStarRotY * ((obj().comp().mainCamera().getCenter().x - obj().location().pos().x) / param.mZStarOffset.x);
    {
        NodeAccessor node = obj().model().model().nodes().at(1);
        node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(0.0f, rotY, 0.0f)));
    }
    if (mIndex != 0 && mIndex < 5 && mCount % mConfig._C == 0) {
        reqStar();
        obj().effect().state().requestN(static_cast<effect::Kind>(0x4C9), 3);
        obj().soundSE().normal().start(0x462);
    }
}

void StateZStar::procMove() {
    Vector3 target = mPoints[mIndex];
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mConfig._0);
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    obj().location().setPos(Math::LinearInterpolation(mBasePos, target, rate));
}

void StateZStar::procFixPos() {}

void StateZStar::reqStar() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.weaponCtrl().clearReqBuff();
    WeaponCtrl::ReqData data;
    data._0 = 10;
    data._4 = Vector2::ZERO.x;
    data._8 = Vector2::ZERO.y;
    custom.weaponCtrl().addReqData(data);
    custom.weaponCtrl().request();
}

}}}}  // namespace scn::step::boss::roah
