#include "scn/step/enemy/chilly/Custom.h"

#include "hel/math/Vector3.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x1a7));
    return false;
}

void Custom::setupSuperEnemyEffect() {
    hel::math::Vector3 center = obj().location().toCenter();
    obj().effect().super().requestN(effect::KIND_132, 0, center);
    obj().effect().super().requestN(static_cast<effect::Kind>(0x30a), 1);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
