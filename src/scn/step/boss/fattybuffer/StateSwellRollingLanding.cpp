#include "scn/step/boss/fattybuffer/StateSwellRollingLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateSwellWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellRollingLanding::StateSwellRollingLanding(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0x1B);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_4);
    obj().move().resetSpeedV();
    const Param& param = obj().param().fattybuffer();
    Vector2 pos(param._28.x * obj().target().getSign(), param._28.y);
    Vector2 speed(param._30.x * obj().target().getSign(), param._30.y);
    pos.scale(obj().model().getTotalScale().getXY());
    Utility::GenerateStarEffect(obj(), pos, speed, map::BinEnemyVariation_StarBound);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
}

StateSwellRollingLanding::~StateSwellRollingLanding() {}

void StateSwellRollingLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateSwellWait, Boss*>(objPtr());
    }
}

void StateSwellRollingLanding::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateSwellRollingLanding::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
