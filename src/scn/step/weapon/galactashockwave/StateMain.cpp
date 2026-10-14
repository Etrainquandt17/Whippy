#include "scn/step/weapon/galactashockwave/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Utility.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/galactashockwave/Param.h"
#include "snd/SERequestor.h"

using hel::geo::Rect;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace weapon {
namespace galactashockwave {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon), _8(0), _C(false) {
    const Param& param = obj().param().galactaShockWave();
    obj().target().setIsRightDir(obj().move().velocity().x > 0.0f);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x21F));
    Vector2 center(param._4 * obj().target().getSign(), param._8);
    obj().objColl().addAttack(0, param._0, center);
    obj().objColl().setAttackCenter(0, center);
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x44C), 0, param._C);
    obj().soundSE().start(0x390);
}

void StateMain::procAnim() {}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {
    if (!_C) {
        Rect rect = obj().comp().mainCamera().getViewRect();
        Vector2 pos = obj().location().pos().getXY();
        if (!rect.isInclude(pos.x, pos.y)) {
            reqStar();
        }
    }
    if (obj().mapColl().isHit()) {
        obj().dead();
    }
}

void StateMain::reqStar() {
    _C = true;
    f32 sign = obj().target().getSign();
    Vector2 offset(-0.5f * sign, 0.0f);
    Vector2 velocity(-0.02f * sign, 0.19f);
    Utility::GenerateStarEffect(obj(), offset, velocity, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::weapon::galactashockwave
