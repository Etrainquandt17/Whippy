#include "scn/step/boss/fattybuffer/StateStampLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStampLanding::StateStampLanding(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0xF);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetSpeedV();
    const Param& param = obj().param().fattybuffer();
    Vector2 pos = param._28;
    Vector2 speed = param._30;
    pos.scale(obj().model().getTotalScale().getXY());
    Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
    Utility::ControlHateOnAction(obj());
}

StateStampLanding::~StateStampLanding() {}

void StateStampLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateStampLanding::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateStampLanding::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
