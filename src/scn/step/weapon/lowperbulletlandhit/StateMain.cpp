#include "scn/step/weapon/lowperbulletlandhit/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/LandConstraint.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

using hel::math::Direction3;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace lowperbulletlandhit {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(0), _10(false), _11(false) {
    switch (obj().variation()) {
    case 0:
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x39D), 0, Direction3::BASIS);
        obj().soundSE().start(0x55C);
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BA));
        obj().objColl().addAttack(0, 0.5f);
        _8 = 60;
        break;
    case 1:
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x39E), 0, Direction3::BASIS, Vector3(0.0f, 0.5f, 0.0f));
        obj().soundSE().start(0x55B);
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BB));
        obj().objColl().addAttack(0, 0.5f, Vector2(0.0f, 0.5f));
        _8 = 25;
        break;
    case 2:
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x3A0), 0, Direction3::BASIS, Vector3(0.0f, 0.5f, 0.0f));
        obj().effect().normal().requestND(
            static_cast<effect::Kind>(0x39E), 0, Direction3::BASIS, Vector3(0.0f, 0.5f, 0.0f), 0.6f);
        obj().soundSE().start(0x55B);
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BB));
        obj().objColl().addAttack(0, 0.3f, Vector2(0.0f, 0.5f));
        _8 = 25;
        _C = 4;
        break;
    case 3:
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x3A7), 0, Direction3::BASIS);
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x3A3), 0, Direction3::BASIS);
        obj().soundSE().start(0x55F);
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BC));
        obj().objColl().addAttack(0, 1.0f, Vector2(0.0f, 0.5f));
        _8 = 30;
        break;
    }
    obj().move().setSpeedV(-0.05f);
}

void StateMain::procAnim() {
    if (_8 != 0) {
        _8--;
    } else {
        obj().dead();
    }
    if (_C != 0) {
        _C--;
        if (_C == 0 && obj().variation() == 2) {
            obj().objColl().addAttack(0, 0.1f, Vector2(0.0f, 10.0f), Vector2(0.0f, 0.0f));
        }
    }
}

void StateMain::procMove() {
    gobj::MoveParamDecel decel = gobj::MoveParamDecel::Create(0.005f);
    gobj::MoveParamFall fall = gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f);
    if (_11) {
        if (_10) {
            obj().move().groundDecel(decel);
        } else {
            obj().move().airDecelFall(decel, fall);
        }
    } else {
        obj().move().decel(gobj::MoveParamDecel::Create(0.01f));
    }
}

void StateMain::procFixPos() {
    if (obj().mapColl().result().mIsHitFloor) {
        _10 = true;
        _11 = true;
        obj().move().resetSpeedV();
        obj().landConstraint().setMode(static_cast<chara::LandConstraint::Mode>(2));
    } else {
        _10 = false;
        obj().landConstraint().resetMode();
    }
}

}}}}  // namespace scn::step::weapon::lowperbulletlandhit
