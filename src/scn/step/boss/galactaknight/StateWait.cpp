#include "scn/step/boss/galactaknight/StateWait.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().brainCtrl().toValid();
    obj().model().reqScript(0);
    obj().hateCtrl().fix();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateWait::procMove() {}

void StateWait::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
