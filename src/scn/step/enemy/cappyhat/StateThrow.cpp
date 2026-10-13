#include "scn/step/enemy/cappyhat/StateThrow.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/cappy/Custom.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappyhat {

StateThrow::StateThrow(Enemy* enemy, u64 ownerUid) : StateBase(enemy), mOwnerUid(ownerUid) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().move().setSpeedV(0.2f);
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x199));
}

StateThrow::~StateThrow() {
    util::ObjRefHandle<Enemy> owner = obj().comp().enemyManager().getEnemyByOCollOwnerUID(mOwnerUid);
    if (owner.isAlive()) {
        hel::common::DynamicCastToRef<cappy::Custom, ICustom>(owner->custom()).setValidTurn(true);
    }
}

void StateThrow::procMove() {
    obj().move().airDecelFall(gobj::MoveParamDecel::Create(0.001f), gobj::MoveParamFall::Create(0.2f, 0.006f, 0.005f));
}

void StateThrow::procFixPos() {
    util::ObjRefHandle<Enemy> owner = obj().comp().enemyManager().getEnemyByOCollOwnerUID(mOwnerUid);
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    if (owner.isAlive()) {
        if (obj().move().velocity().y < 0.0f) {
            if (obj().location().pos().squareDistance(
                    owner->location().pos() - hel::math::Vector3(0.0f, 0.3f * scale, 0.0f)) < 1.5f * scale * scale) {
                cappy::Custom& custom = hel::common::DynamicCastToRef<cappy::Custom, ICustom>(owner->custom());
                if (custom.isCanHat()) {
                    custom.returnHat();
                    obj().dead();
                }
            }
        }
    }
    if (obj().mapColl().result().mIsHitFloor) {
        obj().comp().permEffect().normal().requestP(
            static_cast<effect::Kind>(0x127), obj().location().pos() + hel::math::Vector3(0.0f, 0.2f * scale, 0.0f));
        obj().dead();
    }
}

}
}
}
}
