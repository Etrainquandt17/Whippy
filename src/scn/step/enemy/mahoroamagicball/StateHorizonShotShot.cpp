#include "scn/step/enemy/mahoroamagicball/StateHorizonShotShot.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
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

StateHorizonShotShot::StateHorizonShotShot(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().nururi().setValid(false);
    f32 centerX = obj().comp().mainCamera().getCenter().x;
    obj().target().setIsRightDir(obj().location().pos().x < centerX);
    obj().model().reqScript(8);
    obj().move().setVelocity(hel::math::Vector3(0.2f * obj().target().getSign(), 0.0f, 0.0f));
    obj().soundSE().start(0x436);
}

StateHorizonShotShot::~StateHorizonShotShot() {}

void StateHorizonShotShot::procAnim() {}

void StateHorizonShotShot::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateHorizonShotShot::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || obj().mapColl().result().isHitWall()) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::mahoroamagicball
