#include "scn/step/weapon/metabeam/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Direction3.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "ocoll/Attack.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/metabeam/Param.h"

using hel::math::Direction3;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace weapon {
namespace metabeam {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), mFrame(0) {
    const Param& param = obj().param().metaBeam();
    f32 sign = obj().target().getSign();
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x12A));
    obj().objColl().addAttack(0, param._4, Vector2(sign * param._8, 0.0f), Vector2(sign * -param._8, 0.0f));
    Direction3 dir;
    dir.mFront = Vector3::BASIS_X;
    dir.mFront *= obj().target().getSign();
    dir.restructFrontUp();
    obj().effect().normal().requestND(static_cast<effect::Kind>(0x444), 0, dir);
}

void StateMain::procAnim() {
    if (++mFrame >= obj().param().metaBeam()._0) {
        obj().dead();
    }
}

void StateMain::procMove() {
    const Param& param = obj().param().metaBeam();
    obj().move().decel(param._C);
}

void StateMain::procFixPos() {
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide()) {
        obj().dead();
    }
    if (obj().objColl().attack().isCollideGimmick()) {
        obj().dead();
    }
}

}}}}  // namespace scn::step::weapon::metabeam
