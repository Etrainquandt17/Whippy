#include "scn/step/boss/lowper/StateWait.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    commonInit(DynamicCastToRef<Custom, ICustom>(obj().custom()).waftMoveCtrl().getCenter());
}

StateWait::StateWait(Boss* boss, const Vector3& offset) : StateBase(boss) {
    commonInit(obj().basePos().toVector3() + offset);
}

StateWait::~StateWait() {}

void StateWait::procAnim() {}

void StateWait::procMove() {}

void StateWait::procFixPos() {
    f32 baseX = obj().basePos().x;
    bool isRight = obj().location().pos().x < baseX;
    obj().target().setIsRightDir(isRight);
}

void StateWait::commonInit(const Vector3& pos) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    const Param& param = obj().param().lowper();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().brainCtrl().toValid();
    obj().model().reqScript(0);
    obj().hateCtrl().fix();
    custom.waftMoveCtrl().setCenter(pos);
    custom.waftMoveCtrl().setMoveIntpRate(param._18);
    custom.waftMoveCtrl().setWaveWidth(param._14);
}

}}}}  // namespace scn::step::boss::lowper
