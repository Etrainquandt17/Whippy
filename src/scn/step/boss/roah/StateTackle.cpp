#include "scn/step/boss/roah/StateTackle.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/CustomFlash.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"
#include "snd/SERequestor.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateTackle::StateTackle(Boss* boss, Config config)
    : StateBase(boss), mCount(0), _C(0), mStartPos(), mGoalPos(), mConfig(config), mBaseRotX(0.0f), mPrevRate(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(21);
    mStartPos = obj().location().pos();
    mGoalPos = mStartPos + Vector3::BASIS_X * mConfig._4 * -obj().target().getSign();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_TACKLE);
    obj().guard().setType(GUARD_TYPE_6);
    obj().move().resetVelocity();
}

StateTackle::~StateTackle() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().soundSE().loop().stop();
    obj().effect().normal().releaseAndVanish();
    obj().move().resetVelocity();
    obj().flash().custom().setIsValid(false);
    custom.rotCtrl().toValid();
}

void StateTackle::procAnim() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount < mConfig._0) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (mCount == 1) {
        mBaseRotX = custom.rotCtrl().getRotX();
        custom.rotCtrl().toInvalid();
    }
    if (mCount == param.mTackleSEFrame) {
        obj().soundSE().normal().start(0x460);
    }
    f32 sin = Math::SinDegF(90.0f * (static_cast<f32>(mCount) / static_cast<f32>(mConfig._0)));
    f32 rotX = 720.0f * sin - mBaseRotX;
    {
        NodeAccessor node = obj().model().model().nodes().at(1);
        Matrix34 mtx = Matrix34::CreateRotXYZDeg(Vector3(rotX, 0.0f, 0.0f)) *
                       Matrix34::CreateRotXYZDeg(Vector3(0.0f, param.mRotYMax * obj().target().getSign(), 0.0f));
        node.localMtx().setRTMtx(mtx);
    }
    if (obj().location().prevPos().x < obj().location().pos().x && mCount % 5 == 0) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(1));
    }
}

void StateTackle::procMove() {
    const Param& param = obj().param().roah();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mConfig._0);
    Vector3 pos = mStartPos;
    f32 ease = (1.0f - Math::CosDegF(90.0f * t)) * (1.0f - Math::CosDegF(90.0f * t));
    f32 rate = Math::SinDegF(180.0f * ease);
    pos.x = rate * (mGoalPos.x - mStartPos.x) + mStartPos.x;
    pos.x += mConfig._8 * obj().target().getSign() *
             ((1.0f - Math::CosDegF(90.0f * t)) *
              ((1.0f - Math::CosDegF(90.0f * t)) * (1.0f - Math::CosDegF(90.0f * t))));
    f32 wave = 0.0f;
    if (mPrevRate < rate) {
        wave = Math::SinDegF(180.0f * Math::SinDegF(90.0f * rate));
    }
    mPrevRate = rate;
    pos.z -= wave * param.mTackleDepth;
    obj().location().setPos(pos);
}

void StateTackle::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
