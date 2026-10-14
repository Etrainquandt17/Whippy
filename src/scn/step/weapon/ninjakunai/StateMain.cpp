#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/ninjakunai/StateMain.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "ocoll/Attack.h"
#include "ocoll/AttackResult.h"
#include "scn/step/Component.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/ocoll/HitResistLv.h"
#include "scn/step/weapon/Effect.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjakunai/Param.h"
#include "scn/step/weapon/ninjakunai/StateStickEnemy.h"
#include "scn/step/weapon/ninjakunai/StateStickWall.h"
#include "scn/step/weapon/ninjakunai/StateVanish.h"
#include "scn/step/weapon/ninjakunai/Utility.h"

using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

StateMain::StateMain(Weapon* weapon) : StateBase(weapon) {
    const Param& param = obj().param().ninjaKunai();
    f32 sign = obj().target().getSign();
    f32 radius = param._10;
    f32 offsetX = sign * param._14;
    mcoll::detail::ShapeDiamondContext shape(
        Vector2(offsetX, 0.0f), -radius, 0.0f, radius, -radius, 0.0f, radius
    );
    obj().mapColl().changeActorShape(shape);
    obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0xD6));
    obj().objColl().addAttack(0, param._18, Vector2(sign * param._1C, param._20));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0x49C), 0, Vector3(0.0f, param._24, param._28));
}

StateMain::~StateMain() {
    obj().objColl().clearAttack();
}

void StateMain::procAnim() {
    Utility::Rotate(obj());
}

void StateMain::procMove() {
    obj().move().decel(gobj::MoveParamDecel::Zero());
}

void StateMain::procFixPos() {}

void StateMain::procConstraint() {}

void StateMain::procObjCollReact() {
    if (obj().objColl().attack().isCollide()) {
        obj().effect().normal().release();
        if (obj().objColl().attack().getCollidedHitResistLv() >= ocoll::HIT_RESIST_LV_REPEL) {
            obj().stateChanger().setNextState<StateVanish, Weapon*, VanishKind>(&obj(), VANISH_KIND_REPEL_ROLL);
        } else {
            u64 uid = obj().objColl().attack().result().getData(0).mOwnerID;
            obj().stateChanger().setNextState<StateStickEnemy, Weapon*, ObjRefHandle<enemy::Enemy> >(
                &obj(), obj().comp().enemyManager().getEnemyByOCollOwnerUID(uid)
            );
        }
    } else if (obj().objColl().attack().isCollideGimmick()) {
        obj().dead();
    } else if (obj().mapColl().result().isHitWall() || (obj().mapColl().isHit() && 0.0f != obj().mapColl().normal().x)) {
        obj().effect().normal().release();
        switch (static_cast<int>(obj().variation())) {
        case 0:
            if (!obj().mapColl().result().isHitWall()) {
                obj().stateChanger().setNextState<StateVanish, Weapon*, VanishKind>(&obj(), VANISH_KIND_DROP_ROLL);
            } else {
                Vector3 velocity = obj().mapColl().normal().toVector3();
                velocity *= -0.1f;
                obj().move().setVelocity(velocity);
                obj().stateChanger().setNextState<StateStickWall, Weapon*>(&obj());
            }
            break;
        case 1:
            obj().stateChanger().setNextState<StateVanish, Weapon*, VanishKind>(&obj(), VANISH_KIND_DROP_ROLL);
            break;
        case 2:
            obj().stateChanger().setNextState<StateVanish, Weapon*, VanishKind>(&obj(), VANISH_KIND_DROP);
            break;
        }
    }
}

}}}}  // namespace scn::step::weapon::ninjakunai
