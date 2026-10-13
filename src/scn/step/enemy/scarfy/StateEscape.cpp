#include "scn/step/enemy/scarfy/StateEscape.h"

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
#include "scn/step/enemy/scarfy/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

StateEscape::StateEscape(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(0);
}

void StateEscape::procMove() {
    const ParamData& param = obj().param().scarfy();
    if (Utility::IsPlayerExist(obj())) {
        hel::math::Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
        obj().target().setIsRightDir(obj().location().pos().x > playerPos.x);
        hel::math::Vector3 velocity = obj().move().velocity();
        velocity.x += param.mEscapeAccelX * getSpd() * obj().target().getSign();
        velocity.x = hel::math::Math::Limit(velocity.x, param.mEscapeSpeedLimitX * getSpdLimit());
        velocity.y += param.mEscapeAccelY * getSpd();
        velocity.y = hel::math::Math::Limit(velocity.y, param.mEscapeSpeedLimitY * getSpdLimit());
        obj().move().setVelocity(velocity);
    }
    obj().move().airDecelFall(gobj::MoveParamDecel::Zero(), gobj::MoveParamFall::Zero());
}

f32 StateEscape::getSpdLimit() {
    const ParamData& param = obj().param().scarfy();
    switch (static_cast<u32>(obj().level())) {
    case 0:
        return param.mLevel[0].mSpdLimit;
    case 1:
        return param.mLevel[1].mSpdLimit;
    case 2:
        return param.mLevel[2].mSpdLimit;
    case 3:
        return param.mLevel[3].mSpdLimit;
    default:
        return param.mLevel[4].mSpdLimit;
    }
}

f32 StateEscape::getSpd() {
    const ParamData& param = obj().param().scarfy();
    switch (static_cast<u32>(obj().level())) {
    case 0:
        return param.mLevel[0].mSpd;
    case 1:
        return param.mLevel[1].mSpd;
    case 2:
        return param.mLevel[2].mSpd;
    case 3:
        return param.mLevel[3].mSpd;
    default:
        return param.mLevel[4].mSpd;
    }
}

}}}}  // namespace scn::step::enemy::scarfy
