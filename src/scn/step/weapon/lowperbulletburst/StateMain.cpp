#include "scn/step/weapon/lowperbulletburst/StateMain.h"

#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Weapon.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace weapon {
namespace lowperbulletburst {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(0) {
    switch (obj().variation()) {
    case 0:
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x39D), 0, hel::math::Direction3::BASIS);
        obj().soundSE().start(0x55C);
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BA));
        obj().objColl().addAttack(0, 0.5f);
        _8 = 60;
        break;
    case 1:
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x39F), 0, hel::math::Direction3::BASIS);
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x39E), 0, hel::math::Direction3::BASIS);
        obj().soundSE().start(0x55B);
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BB));
        obj().objColl().addAttack(0, 0.5f);
        _8 = 50;
        _C = 4;
        break;
    case 2:
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x3A7), 0, hel::math::Direction3::BASIS, hel::math::Vector3(0.0f, -0.5f, 0.0f));
        obj().effect().normal().requestND(static_cast<effect::Kind>(0x3A3), 0, hel::math::Direction3::BASIS, hel::math::Vector3(0.0f, -0.5f, 0.0f));
        obj().soundSE().start(0x55F);
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BC));
        obj().objColl().addAttack(0, 1.0f);
        _8 = 30;
        break;
    }
}

void StateMain::procAnim() {
    if (_8 != 0) {
        _8--;
    } else {
        obj().dead();
    }
    if (_C != 0) {
        _C--;
        if (_C == 0 && obj().variation() == 1) {
            obj().objColl().addAttack(0, 0.1f, hel::math::Vector2(0.0f, -10.0f), hel::math::Vector2(0.0f, 0.0f));
        }
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::lowperbulletburst
