#include "scn/step/enemy/kabu/StateFall.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/common/StateLanding.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

StateFall::StateFall(Enemy* enemy) : StateBase(enemy) {
    mSpeed = Math::Abs(obj().move().velocity().x);
    obj().footState().setAir();
}

StateFall::~StateFall() {}

void StateFall::procMove() {
    const common::ParamData& param = obj().param().common();
    const gobj::MoveParamAccel& accel = gobj::MoveParamAccel::Create(mSpeed, mSpeed, 0.0f);
    obj().move().airAccelFall(obj().target().isRightDir(), accel, param.mFall);
}

void StateFall::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<common::StateLanding, Enemy*>(objPtr());
    }
    if (obj().mapColl().result().isHitWall()) {
        obj().target().setIsRightDir(!obj().target().isRightDir());
    }
}

}}}}  // namespace scn::step::enemy::kabu
