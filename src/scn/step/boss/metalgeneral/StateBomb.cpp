#include "scn/step/boss/metalgeneral/StateBomb.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateBomb::StateBomb(Boss* boss, Config config) : StateBase(boss), mConfig(config) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x20);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
}

StateBomb::~StateBomb() {}

void StateBomb::procAnim() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        Vector2 pos = obj().location().pos().getXY();
        pos += Vector2(param._1B0.x * obj().target().getSign(), param._1B0.y);
        Vector2 speed(mConfig.mSpeed.x * obj().target().getSign(), mConfig.mSpeed.y);
        custom.weaponCtrl().reqBomb(pos, speed, mConfig.mIsBig);
    }
}

void StateBomb::procMove() {}

void StateBomb::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
