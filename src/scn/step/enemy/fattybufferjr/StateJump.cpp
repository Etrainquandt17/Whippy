#include "scn/step/enemy/fattybufferjr/StateJump.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateLanding.h"
#include "scn/step/enemy/fattybufferjr/ParamData.h"

using app::Random;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferjr {

StateJump::StateJump(Enemy* enemy, const Vector3& velocity) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(8);
    obj().move().setVelocity(velocity);
    obj().target().setIsRightDir(Random::RandBool(0.5f));
}

void StateJump::procAnim() {}

void StateJump::procMove() {
    const ParamData::Air& param = obj().param().fattybufferjr().mJump;
    obj().move().airDecelFall(param.mDecel, param.mFall);
}

void StateJump::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::fattybufferjr
