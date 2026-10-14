#include "scn/step/enemy/grandlowperbullet/StateHomingShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace grandlowperbullet {

StateHomingShot::StateHomingShot(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().soundSE().start(0x3b1);
}

StateHomingShot::~StateHomingShot() {}

void StateHomingShot::procAnim() {}

void StateHomingShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateHomingShot::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::grandlowperbullet
