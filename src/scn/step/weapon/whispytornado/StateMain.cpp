#include "scn/step/weapon/whispytornado/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/whispytornado/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace whispytornado {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mSpeed(0.0f) {
    const Param& param = obj().param().whispyTornado();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1C7));
    obj().objColl().addAttack(0, param._4, hel::math::Vector2(param._8), hel::math::Vector2(param._10));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x53E), 0);
#ifdef VERSION_SUKK01
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x651), 0);
#else
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x650), 0);
#endif
}

void StateMain::procAnim() {}

void StateMain::procMove() {
    mSpeed += obj().param().whispyTornado()._0;
    obj().move().setSpeedV(mSpeed + obj().move().velocity().y);
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::whispytornado
