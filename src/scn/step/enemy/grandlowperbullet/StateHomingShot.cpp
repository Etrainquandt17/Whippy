#include "scn/step/enemy/grandlowperbullet/StateHomingShot.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
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

}
}
}
}
