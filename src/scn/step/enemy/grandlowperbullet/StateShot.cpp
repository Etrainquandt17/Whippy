#include "scn/step/enemy/grandlowperbullet/StateShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/VacuumReceiver.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

StateShot::StateShot(Enemy* enemy) : StateBase(enemy), mXluFrame(3) {
    obj().footState().setAir();
    obj().vacuumReceiver().setIsValid(false);
    obj().objColl().setBodyCollStateXlu();
    obj().model().reqScript(0);
}

StateShot::~StateShot() {
    if (mXluFrame != 0) {
        obj().objColl().setBodyCollStateNormal();
        obj().vacuumReceiver().setIsValid(true);
    }
}

void StateShot::procAnim() {
    if (mXluFrame != 0 && --mXluFrame == 0) {
        obj().objColl().setBodyCollStateNormal();
        obj().vacuumReceiver().setIsValid(true);
    }
}

void StateShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateShot::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
