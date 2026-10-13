#include "scn/step/boss/fattybuffer/StateCannonEnd.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateCannonEnd::StateCannonEnd(Boss* boss, f32 angle) : StateBase(boss), mAngle(angle) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x11);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_13);
    updateSRT();
    Utility::ControlHateOnAction(obj());
}

StateCannonEnd::~StateCannonEnd() {
    obj().model().model().nodes().at(3).localMtx().reset();
}

void StateCannonEnd::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
    }
    if (!hel::math::Math::EqZero(mAngle)) {
        mAngle = hel::math::Math::Interpolate(mAngle, 0.0f, obj().param().fattybuffer()._A8);
        updateSRT();
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateCannonEnd::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateCannonEnd::procFixPos() {}

void StateCannonEnd::updateSRT() {
    hel::math::Vector3 rot(-mAngle, 0.0f, 0.0f);
    g3d::NodeAccessor node = obj().model().model().nodes().at(3);
    node.localMtx().setRTMtx(hel::math::Matrix34::CreateRotXYZDeg(rot));
}

}}}}  // namespace scn::step::boss::fattybuffer
