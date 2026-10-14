#include "scn/step/boss/hrd3/StateWaitFar.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateWaitFar::StateWaitFar(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().brainCtrl().toValid();
    obj().target().setIsRightDir(false);
    obj().model().reqScript(0);
    obj().hateCtrl().fix();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
}

StateWaitFar::~StateWaitFar() {}

void StateWaitFar::procAnim() {}

void StateWaitFar::procMove() {
    const Param& param = obj().param().hrd3();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector3 goal(custom.landCtrl().getCenterX(), param._F8 + custom.landCtrl().getFloorY(), param._FC);
    obj().location().setPos(Math::LinearInterpolation(obj().location().pos(), goal, 0.05f));
}

void StateWaitFar::procFixPos() {}

}}}}  // namespace scn::step::boss::hrd3
