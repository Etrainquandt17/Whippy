#include "scn/step/boss/lowper/StateShotBulletStart.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateShotBulletStart::StateShotBulletStart(Boss* boss, f32 height) : StateBase(boss), mPos(), _10(0), _14(0.3f) {
    f32 baseX = obj().basePos().x;
    f32 sign = obj().location().pos().x >= baseX ? 1.0f : -1.0f;
    mPos = obj().basePos() + Vector2(5.0f * sign, height);
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(5);
}

StateShotBulletStart::~StateShotBulletStart() {}

void StateShotBulletStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateShotBulletStart::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.waftMoveCtrl().setMoveIntpRate(0.05f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(mPos.toVector3());
}

void StateShotBulletStart::procFixPos() {
    f32 baseX = obj().basePos().x;
    bool isRight = obj().location().pos().x < baseX;
    obj().target().setIsRightDir(isRight);
}

}}}}  // namespace scn::step::boss::lowper
