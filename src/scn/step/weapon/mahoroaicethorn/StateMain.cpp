#include "scn/step/weapon/mahoroaicethorn/StateMain.h"

#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/core/AreaOperation.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaicethorn {

// TODO: an inline function that takes both coordinates by value; where it lives is not known.
inline void t_Trans(hel::geo::Rect& rect, f32 x, f32 y) {
    rect.trans(x, y);
}

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mLifetime(), mAreaId(0) {
    obj().mapColl().setValid(false);
    mLifetime.set(240);
    obj().model().rotCtrl().setValid(false);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x206));
    obj().objColl().addAttack(0, 0.5f, hel::math::Vector2(-0.5f, 0.0f), hel::math::Vector2(0.5f, 0.0f));
    obj().objColl().setAttackCenter(0, hel::math::Vector2::ZERO);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x40A), 0);
    hel::geo::Rect rect(0.5f, -0.5f, -1.2f, 1.2f);
    t_Trans(rect, obj().location().pos().x, obj().location().pos().y);
    mAreaId = obj().comp().areaOperation().createFrozenArea(rect);
}

StateMain::~StateMain() {
    obj().comp().areaOperation().removeFrozenArea(mAreaId);
}

void StateMain::procAnim() {
    mLifetime.update();
    if (mLifetime.isDead()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x409), obj().location().pos());
        ::ocoll::Owner& owner = obj().objColl().owner();
        Desc desc(static_cast<Kind>(0x98), 0, static_cast<ostop::Flag>(8), obj().location().pos().getXY(), hel::math::Vector2::ZERO, owner);
        obj().comp().weaponManager().request(desc);
        obj().dead();
    }
}

void StateMain::procMove() {}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::mahoroaicethorn
