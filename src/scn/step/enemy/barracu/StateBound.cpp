#include "scn/step/enemy/barracu/StateBound.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

StateBound::StateBound(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().model().rotCtrl().setRotHTargetDefault(90.0f);
    obj().model().rotCtrl().initRotH(90.0f);
    obj().model().rotCtrl().setRotHIntpRate(0.07f);
}

void StateBound::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.0001f), gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f));
}

void StateBound::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        obj().move().setSpeedV(0.1f);
        f32 speed = app::Random::Rand(2) == 0 ? 0.02f : -0.02f;
        obj().move().setSpeedH(speed);
    }
}

}
}
}
}
