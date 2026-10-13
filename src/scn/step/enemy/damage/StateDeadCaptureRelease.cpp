#include "scn/step/enemy/damage/StateDeadCaptureRelease.h"

#include "app/Application.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Random.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/DamageFlash.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/ObjCollReact.h"
#include "scn/step/enemy/VacuumReceiver.h"
#include "scn/step/enemy/damage/Utility.h"

namespace scn {
namespace step {
namespace enemy {
namespace damage {

StateDeadCaptureRelease::StateDeadCaptureRelease(Enemy* enemy, bool isRight) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(6);
    obj().target().setIsRightDir(!isRight);
    hel::math::Vector3 velocity = hel::math::Vector3::BASIS_X;
    f32 angle = 50.0f;
    f32 width = 10.0f;
    angle += width * app::Application::Object().random().randAF();
    velocity.rotate(hel::math::Vector3::BASIS_Z, 0.017453292f * angle);
    velocity.x *= enemy->target().getSign();
    velocity *= 0.1f;
    enemy->move().setVelocity(velocity);
    if (obj().move().velocity().x != 0.0f) {
        bool isLeft = obj().move().velocity().x < 0.0f;
        obj().target().setIsRightDir(isLeft);
    }
    obj().objColl().bodyColl().setStateXlu();
    obj().objCollReact().setDamageState();
    obj().nururi().setValid(false);
    obj().captureReceiver().setCanCapture(false);
    obj().vacuumReceiver().setIsValid(false);
    obj().hitPoint().set(0);
    obj().damageFlash().set(ocoll::ELEMENT_0);
}

StateDeadCaptureRelease::~StateDeadCaptureRelease() {}

void StateDeadCaptureRelease::procAnim() {
    mFrame++;
}

void StateDeadCaptureRelease::procMove() {
    Utility::UpdateMoveRate(&obj());
    Utility::EmDamageUtility_Move(&obj());
}

void StateDeadCaptureRelease::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor || mFrame > 30) {
        obj().deadWithEffect();
    }
}

}}}}  // namespace scn::step::enemy::damage
