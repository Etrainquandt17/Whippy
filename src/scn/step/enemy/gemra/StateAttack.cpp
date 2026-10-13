#include "scn/step/enemy/gemra/StateAttack.h"

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
namespace gemra {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().move().resetSpeedH();
    obj().move().resetSpeedV();
    obj().model().rotCtrl().setRotHTarget(90.0f);
}

StateAttack::~StateAttack() {
    obj().model().rotCtrl().resetRotTarget();
    obj().objColl().clearAttack();
    obj().soundSE().stop();
    obj().effect().state().releaseAndVanish();
}

void StateAttack::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().model().rotCtrl().resetRotTarget();
        obj().brainCtrl().toValid();
    }
}

}
}
}
}
