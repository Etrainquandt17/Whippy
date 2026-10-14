#include "scn/step/boss/hrd3/StatePressLanding.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/boss/hrd3/StateWait.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StatePressLanding::StatePressLanding(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::TurnHatedHero(obj());
    Utility::ControlHateOnAction(obj());
    u32 scriptKind = 0x15;
    if (custom.partsCtrl().isExistHipNeedle()) {
        scriptKind = 0x16;
    }
    obj().model().reqScript(scriptKind);
    reqStar();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    obj().guard().setType(static_cast<GuardType>(2));
}

StatePressLanding::~StatePressLanding() {}

void StatePressLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StatePressLanding::procMove() {}

void StatePressLanding::procFixPos() {}

void StatePressLanding::reqStar() {
    const Param& param = obj().param().hrd3();
    Vector2 pos = param._14;
    Vector2 speed = param._24;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::boss::hrd3
