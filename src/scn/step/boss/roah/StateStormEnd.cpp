#include "scn/step/boss/roah/StateStormEnd.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "util/ObjList.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateStormEnd::StateStormEnd(Boss* boss, Config config) : StateBase(boss), mConfig(config) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(18);
    custom.mahoroaCtrl().getCustom().reqMotionStormEnd();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetVelocity();
#ifdef VERSION_SUKK01
    obj().effect().state().requestN(static_cast<effect::Kind>(0x638), 4);
#else
    obj().effect().state().requestN(static_cast<effect::Kind>(0x637), 4);
#endif
    if (mConfig.mKind == StormKind_Circle) {
        obj().model().model().nodes().at(1).localMtx().setRTMtx(
            Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, custom.rotCtrl().getLocalMtxTempRot().z)) *
            Matrix34::CreateRotXYZDeg(Vector3(mConfig.mRotX, 0.0f, 0.0f)) *
            Matrix34::CreateRotXYZDeg(Vector3(0.0f, 90.0f * obj().target().getSign(), 0.0f)));
    }
}

StateStormEnd::~StateStormEnd() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!obj().model().isAllEnd()) {
        obj().effect().state().releaseAndVanish();
    }
    if (mConfig.mKind == StormKind_Circle) {
        custom.rotCtrl().toValid();
    }
}

void StateStormEnd::procAnim() {
    const Param& param = obj().param().roah();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (mConfig.mKind == StormKind_Circle) {
        f32 rate = obj().model().anim().frame() / static_cast<f32>(obj().model().anim().totalFrame());
        f32 rotX = mConfig.mRotX * Math::CosDegF(90.0f * rate);
        f32 rotY = Math::LinearInterpolation(90.0f * obj().target().getSign(), param.mRotYMax * obj().target().getSign(),
                                             Math::SinDegF(90.0f * rate));
        f32 rotZ = Math::CosDegF(90.0f * rate) * custom.rotCtrl().getLocalMtxTempRot().z;
        obj().model().model().nodes().at(1).localMtx().setRTMtx(
            Matrix34::CreateRotXYZDeg(Vector3(0.0f, 0.0f, rotZ)) *
            Matrix34::CreateRotXYZDeg(Vector3(rotX, 0.0f, 0.0f)) *
            Matrix34::CreateRotXYZDeg(Vector3(0.0f, rotY, 0.0f)));
        custom.rotCtrl().setLocalMtxTempRot(rotX, rotY, rotZ);
    }
}

void StateStormEnd::procMove() {}

void StateStormEnd::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
