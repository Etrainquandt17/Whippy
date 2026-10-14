#include "scn/step/boss/fattybuffer/StateLanding.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
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

StateLanding::StateLanding(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0xA);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetSpeedV();
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
}

StateLanding::~StateLanding() {}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateLanding::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateLanding::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
