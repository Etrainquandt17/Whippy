#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/ninjablossomstorm/StateMain.h"

#include "gobj/Move.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjablossomstorm/Param.h"
#include "util/ObjRefHandle.h"

using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace ninjablossomstorm {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    obj().setValidAttackRumble(true);
    obj().move().resetVelocity();
#ifdef VERSION_SUKK01
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x62F), 0);
#else
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x62E), 0);
#endif
    obj().model().rotCtrl().initRotH(0.0f);
}

StateMain::~StateMain() {}

void StateMain::procAnim() {
    const Param& param = obj().param().ninjaBlossomStorm();
    mFrame++;
    if (mFrame >= param._8) {
        obj().dead();
        return;
    }
    if (mFrame == param._0) {
        obj().objColl().setAttackCenter(0, Vector2(0.0f, param._14));
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xD8));
        obj().objColl().addAttack(0, param._C, Vector2(param._10, param._14), Vector2(-param._10, param._14));
        obj().objColl().addAttack(0, param._18, Vector2(0.0f, param._1C));
    }
    if (mFrame == param._4) {
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xD9));
        obj().objColl().renewAttack();
    }
}

void StateMain::procMove() {}

void StateMain::procConstraint() {
    ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromObjCollOwnerID(obj().objColl().owner().rootUid());
    if (hero.isAlive()) {
        Vector3 pos = obj().location().pos();
        const hero::Hero& owner = *hero.operator->();
        pos.x = owner.location().pos().x;
        obj().location().setPos(pos);
    }
}

void StateMain::procFixPos() {}

}}}}  // namespace scn::step::weapon::ninjablossomstorm
