#include "scn/step/boss/goliath/StateWallWait.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateWallWait::StateWallWait(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().hateCtrl().fix();
    obj().target().setIsRightDir(obj().location().pos().x < custom.landCtrl().getCenterX());
    obj().model().reqScript(9);
    obj().brainCtrl().toValid();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateWallWait::~StateWallWait() {}

void StateWallWait::procAnim() {}

void StateWallWait::procMove() {}

void StateWallWait::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
