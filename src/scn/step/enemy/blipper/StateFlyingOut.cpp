#include "scn/step/enemy/blipper/StateFlyingOut.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/blipper/ParamData.h"
#include "scn/step/enemy/blipper/StateFall.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

StateFlyingOut::StateFlyingOut(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().move().setSpeedV(obj().param().blipper().mFlyingOutSpeedV);
    Vector2 diff = Utility::GetNearestPlayerPos(obj()) - obj().location().pos().getXY();
    obj().target().setIsRightDir(diff.x >= 0.0f);
}

void StateFlyingOut::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

void StateFlyingOut::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f));
}

void StateFlyingOut::procFixPos() {
    if (!obj().mapColl().result().mIsHitFloor) {
        obj().stateChanger().setNextState<StateFall, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::blipper
