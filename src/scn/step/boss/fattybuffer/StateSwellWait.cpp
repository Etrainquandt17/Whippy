#include "scn/step/boss/fattybuffer/StateSwellWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

StateSwellWait::StateSwellWait(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(0x13);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_4);
    obj().brainCtrl().toValid();
}

StateSwellWait::~StateSwellWait() {}

void StateSwellWait::procAnim() {}

void StateSwellWait::procMove() {
    const Param& param = obj().param().fattybuffer();
    obj().move().groundDecel(param._14);
}

void StateSwellWait::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
