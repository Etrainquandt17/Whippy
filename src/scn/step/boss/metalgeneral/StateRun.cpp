#include "scn/step/boss/metalgeneral/StateRun.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateRun::StateRun(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(9);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::TurnHatedHero(obj());
    obj().move().resetVelocity();
    obj().brainCtrl().toValid();
    Utility::ControlHateOnAction(obj());
}

StateRun::~StateRun() {}

void StateRun::procAnim() {}

void StateRun::procMove() {
    const Param& param = obj().param().metalgeneral();
    obj().move().groundAccel(obj().target().isRightDir(), param._C8);
}

void StateRun::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
