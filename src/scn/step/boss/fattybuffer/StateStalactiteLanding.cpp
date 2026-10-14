#include "scn/step/boss/fattybuffer/StateStalactiteLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateStalactiteLanding::StateStalactiteLanding(Boss* boss, StalactiteJumpKind kind) : StateBase(boss), mKind(kind) {
    const Param& param = obj().param().fattybuffer();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetSpeedV();
    switch (mKind) {
    case STALACTITE_JUMP_KIND_0:
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        obj().model().reqScript(0x25);
        custom.stalactiteCtrl().setRequestData(param._12C);
        break;
    case STALACTITE_JUMP_KIND_1:
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        obj().model().reqScript(0x28);
        custom.stalactiteCtrl().down();
        break;
    case STALACTITE_JUMP_KIND_2:
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
        obj().model().reqScript(0x2B);
        custom.stalactiteCtrl().fall();
        Utility::ControlHateOnAction(obj());
        break;
    case STALACTITE_JUMP_KIND_3:
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
        obj().model().reqScript(0x2E);
        custom.stalactiteCtrl().setRequestData(param._130);
        break;
    case STALACTITE_JUMP_KIND_4:
        obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(7));
        obj().model().reqScript(0x31);
        custom.stalactiteCtrl().fall();
        Utility::ControlHateOnAction(obj());
        break;
    }
    obj().guard().setType(static_cast<GuardType>(2));
}

StateStalactiteLanding::~StateStalactiteLanding() {}

void StateStalactiteLanding::procAnim() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).stalactiteCtrl().requestUpdate();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateStalactiteLanding::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateStalactiteLanding::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
