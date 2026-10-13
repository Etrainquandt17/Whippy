#include "scn/step/enemy/mahoroamagicball/StateVerticalShotShot.h"

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
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace mahoroamagicball {

StateVerticalShotShot::StateVerticalShotShot(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().nururi().setValid(false);
    obj().mapColl().setValid(false);
    obj().model().reqScript(8);
    obj().move().setVelocity(hel::math::Vector3(0.0f, 0.2f, 0.0f));
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
