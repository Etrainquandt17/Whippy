#include "scn/step/boss/dubior/StateDashWallHit.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::math::Direction3;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateDashWallHit::StateDashWallHit(Boss* boss) : StateBase(boss) {
    const Param& param = obj().param().dubior();
    obj().footState().setAir();
    obj().model().reqScript(8);
    obj().brainCtrl().toValid();
    Vector2 pos(param.mDashWallHitStarPos.x * obj().target().getSign(), param.mDashWallHitStarPos.y);
    Vector2 speed(param.mDashWallHitStarSpeed.x * obj().target().getSign(), param.mDashWallHitStarSpeed.y);
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19A));
    Direction3 dir = obj().target().isRightDir() ? Direction3::FRONT_TO_LEFT : Direction3::FRONT_TO_RIGHT;
    obj().effect().normal().requestPD(static_cast<effect::Kind>(0xB4), obj().location().pos() + pos.toVector3(), dir);
}

StateDashWallHit::~StateDashWallHit() {}

void StateDashWallHit::procAnim() {}

void StateDashWallHit::procMove() {
    const Param& param = obj().param().dubior();
    obj().move().decel(param._4C);
}

void StateDashWallHit::procFixPos() {}

}}}}  // namespace scn::step::boss::dubior
