#include "scn/step/boss/goliath/StateSwoopLanding.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateWait.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateSwoopLanding::StateSwoopLanding(Boss* boss) : StateBase(boss) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Utility::ControlHateOnAction(obj());
    obj().model().reqScript(0x11);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    generateStarEffect();
}

StateSwoopLanding::~StateSwoopLanding() {}

void StateSwoopLanding::procAnim() {
    Utility::TurnHatedHero(obj());
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSwoopLanding::procMove() {}

void StateSwoopLanding::procFixPos() {}

void StateSwoopLanding::generateStarEffect() {
    const Param& param = obj().param().goliath();
    Vector2 pos = param._24;
    Vector2 speed = param._2C;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::boss::goliath
