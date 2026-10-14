#include "scn/step/boss/fattybuffer/StateSwellEnd.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateWait.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellEnd::StateSwellEnd(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0x14);
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.mapCollCtrl().setDefault();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_12);
    Utility::ControlHateOnAction(obj());
}

StateSwellEnd::~StateSwellEnd() {}

void StateSwellEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSwellEnd::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateSwellEnd::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
