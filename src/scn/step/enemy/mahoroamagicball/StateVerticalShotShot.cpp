#include "scn/step/enemy/mahoroamagicball/StateVerticalShotShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "snd/SERequestor.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

StateVerticalShotShot::StateVerticalShotShot(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(8);
    obj().move().setVelocity(Vector3(0.0f, 0.2f, 0.0f));
    obj().soundSE().start(0x436);
}

StateVerticalShotShot::~StateVerticalShotShot() {
    obj().mapColl().setValid(true);
}

void StateVerticalShotShot::procAnim() {}

void StateVerticalShotShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateVerticalShotShot::procFixPos() {}

}}}}  // namespace scn::step::enemy::mahoroamagicball
