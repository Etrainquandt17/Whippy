#include "scn/step/boss/metalgeneral/StatePatriotGenerate.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/StatePatriotClimb.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StatePatriotGenerate::StatePatriotGenerate(Boss* boss, Config config) : StateBase(boss), mConfig(config) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    if (mConfig._4) {
        obj().model().reqScript(0x23);
    } else {
        obj().model().reqScript(0x22);
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().move().resetVelocity();
    if (!Math::EqZero(obj().location().pos().z)) {
        obj().model().rotCtrl().setRotHTarget(param._1E0);
    }
}

StatePatriotGenerate::~StatePatriotGenerate() {}

void StatePatriotGenerate::procAnim() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        if (mConfig._4) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StatePatriotClimb, Boss*>(objPtr());
        }
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        Vector3 pos = obj().location().pos();
        pos.x += param._1E4 * obj().target().getSign();
        pos.y += param._1E8;
        custom.weaponCtrl().reqPatriot(pos, mConfig._0, mConfig._4, mConfig._8);
    }
}

void StatePatriotGenerate::procMove() {}

void StatePatriotGenerate::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
