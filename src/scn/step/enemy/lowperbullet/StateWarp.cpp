#include "scn/step/enemy/lowperbullet/StateWarp.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/VacuumReceiver.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {

StateWarp::StateWarp(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(0);
    obj().mapColl().setValid(false);
    obj().objColl().bodyColl().setStateXlu();
    obj().vacuumReceiver().setIsValid(false);
    obj().move().resetVelocity();
}

StateWarp::~StateWarp() {}

void StateWarp::procAnim() {
    mFrame++;
    if (mFrame >= 20) {
        obj().dead();
        return;
    }
    f32 rate = static_cast<f32>(mFrame) / 20.0f;
    f32 width = 0.01f + (1.0f - rate);
    obj().model().setScale(Vector3(width, rate * rate + 1.0f, width));
}

void StateWarp::procMove() {}

void StateWarp::procFixPos() {}

}}}}  // namespace scn::step::enemy::lowperbullet
