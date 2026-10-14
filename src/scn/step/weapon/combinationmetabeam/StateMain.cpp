#include "scn/step/weapon/combinationmetabeam/StateMain.h"

#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Water.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/combinationmetabeam/Param.h"

using hel::math::Direction3;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace combinationmetabeam {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(weapon->param().combinationMetaBeam()._0), _C(1.0f), _10(false) {
    const Param& param = obj().param().combinationMetaBeam();
    obj().model().rotCtrl().setValid(false);
    ocoll::AttackType attackType = static_cast<ocoll::AttackType>(0x16);
    _C = param._24;
    if (obj().variation() == 1) {
        attackType = static_cast<ocoll::AttackType>(0x17);
        _C = param._28;
    } else if (obj().variation() == 2) {
        attackType = static_cast<ocoll::AttackType>(0x18);
        _C = param._2C;
    }
    f32 sign = obj().target().getSign();
    obj().objColl().setAttackType(attackType);
    obj().objColl().addAttack(
        0, param._C * _C, Vector2(sign * param._18 * _C, 0.0f), Vector2(sign * param._14 * _C, 0.0f));
    obj().objColl().setAttackCenter(0, Vector2(sign * param._1C, 0.0f));
    Direction3 dir = obj().target().getDirection3();
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x613), 0, dir, _C);
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x446), 0, dir, _C);
}

void StateMain::procAnim() {
    if (--_8 == 0) {
        obj().dead();
    }
    const Param& param = obj().param().combinationMetaBeam();
    if (_10 && _8 == param._8) {
        obj().objColl().addAttack(0, param._10 * _C);
        obj().objColl().setAttackCenter(0, Vector2::ZERO);
        obj().objColl().renewAttack();
    }
}

void StateMain::procMove() {
    obj().move().decel(obj().param().combinationMetaBeam()._20);
}

void StateMain::procFixPos() {
    if (!_10) {
        if (obj().mapColl().isHit() || obj().water().isInWater()) {
            const Param& param = obj().param().combinationMetaBeam();
            _10 = true;
            _8 = param._4;
            obj().move().resetVelocity();
            obj().effect().normal().release();
            obj().effect().normal().requestN(static_cast<effect::Kind>(0x447), 0, _C);
            obj().objColl().clearAttack();
            obj().mapColl().setValid(false);
        }
    }
}

}}}}  // namespace scn::step::weapon::combinationmetabeam
