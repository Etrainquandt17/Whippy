#include "scn/step/boss/metalgeneral/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
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

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().brainCtrl().toValid();
    obj().hateCtrl().fix();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateWait::procMove() {
    const Param& param = obj().param().metalgeneral();
    obj().move().groundDecel(param._1C);
}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
