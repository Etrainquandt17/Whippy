#include "scn/step/boss/metalgeneral/StateMissile.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateMissile::StateMissile(Boss* boss, u32 index) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    switch (index) {
    case 1:
        obj().model().reqScript(0x17);
        break;
    case 3:
        obj().model().reqScript(0x18);
        break;
    case 5:
        obj().model().reqScript(0x19);
        break;
    case 8:
        obj().model().reqScript(0x1A);
        break;
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    obj().move().resetVelocity();
}

StateMissile::~StateMissile() {}

void StateMissile::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    Vector2 pos = obj().location().pos().getXY();
    pos += Vector2(param._150 * obj().target().getSign(), param._154);
    if (obj().scriptTrigger().get(1)) {
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        custom.weaponCtrl().reqMissile(pos, enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_0);
    }
    if (obj().scriptTrigger().get(2)) {
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        custom.weaponCtrl().reqMissile(pos, enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_1);
    }
    if (obj().scriptTrigger().get(3)) {
        Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
        custom.weaponCtrl().reqMissile(pos, enemy::metalgeneralmissile::StateSpread::SPREAD_KIND_2);
    }
}

void StateMissile::procMove() {}

void StateMissile::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
