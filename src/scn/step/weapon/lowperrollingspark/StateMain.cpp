#include "scn/step/weapon/lowperrollingspark/StateMain.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Culling.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/lowperrollingspark/Custom.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace lowperrollingspark {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(0) {
    obj().culling().setValid(false);
    obj().mapColl().setValid(false);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x39E), 0, 0.5f);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x1BF));
    obj().objColl().addAttack(0, 0.5f);
}

void StateMain::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (_C < custom.getDelayFrame()) {
        _C++;
    } else if (_8 < custom.getTotalFrame()) {
        _8++;
    } else {
        obj().dead();
    }
}

void StateMain::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(_8) / static_cast<f32>(custom.getTotalFrame());
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    f32 angle = rate * (0.017453292f * custom.getRotAngle());
    Vector2 offset = obj().targetPos();
    offset.rotate(angle);
    obj().location().setPos((custom.getCenterPos() + offset).toVector3());
}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::lowperrollingspark
