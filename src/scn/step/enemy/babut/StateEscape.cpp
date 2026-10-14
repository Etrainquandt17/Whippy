#include "scn/step/enemy/babut/StateEscape.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/babut/ParamData.h"

using hel::math::Math;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace babut {

StateEscape::StateEscape(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(7);
}

void StateEscape::procMove() {
    if (Utility::IsPlayerExist(obj())) {
        Vector2 heroPos = Utility::GetNearestPlayerPos(obj());
        obj().target().setIsRightDir(obj().location().pos().x > heroPos.x);
        f32 speed = obj().move().velocity().y;
        speed += obj().param().babut().mEscapeAccelV;
        if (Math::Abs(speed) > obj().param().babut().mEscapeSpeedVMax) {
            speed = (speed < 0.0f ? -1 : 1) * obj().param().babut().mEscapeSpeedVMax;
        }
        obj().move().setSpeedV(speed);
    }
    obj().move().airAccelFall(obj().target().isRightDir(), gobj::MoveParamAccel::Create(0.075f, 0.0035f, 0.0035f), gobj::MoveParamFall::Zero());
}

}}}}  // namespace scn::step::enemy::babut
